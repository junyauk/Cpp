#pragma once
#include <iostream>
#include <memory>
#include <span>
#include <mdspan>
#include <string>
#include <fstream>
#include "pixel.h"

namespace Ex01_ImagePipeline
{
	template<PixelType Pixel>
	class Image
	{
	private:
		uint32_t m_w;			// width pixels
		uint32_t m_h;			// height pixels
		uint32_t m_stride;		// Width bytes
		uint32_t m_aligned_w;	// stride in pixel
		uint32_t m_aligned_size;// whole size of buffer in pixel

		// Note:
		// An element of m_pixels is Pixel,
		// so if any operation for this pointer should be processed in Pixel, not bytes.
		std::unique_ptr<Pixel[]> m_pixels;	// Will be freed at destructor
	public:
		// Rule of Zero
		// This class has got unique_ptr.
		// So move constructor and operator will be automatically added by compiler
		// And also copy constructor and operator will be deleted.
		// If you do want to clone an image later, 
		// you will have to explicitly write a custom cloning method.
		Image(uint32_t width, uint32_t height) :
			m_w(width),	// pixels
			m_h(height)	// pixels
		{
			m_stride = ((m_w * sizeof(Pixel)) + 31) & ~31;	// bytes
			m_aligned_w = m_stride / sizeof(Pixel);			// pixels
			m_aligned_size = m_aligned_w * m_h;				// pixels
			m_pixels = std::make_unique<Pixel[]>(m_aligned_size); // Specify num of elements
		}

		const uint32_t width() const noexcept { return m_w; }
		const uint32_t height() const noexcept { return m_h; }
		const uint32_t stride() const noexcept { return m_stride; }

		std::span<Pixel> row(const uint32_t y) noexcept
		{
			return std::span<Pixel>(m_pixels.get() + (m_aligned_w * y), m_w);
		}
		const std::span<Pixel> row(const uint32_t y) const noexcept
		{
			return std::span<Pixel>(m_pixels.get() + (m_aligned_w * y), m_w);
		}

		Pixel& at(const uint32_t x, const uint32_t y) noexcept
		{
			return m_pixels[((m_aligned_w * y) + x)];
		}
		const Pixel& at(const uint32_t x, const uint32_t y) const noexcept
		{
			return m_pixels[((m_aligned_w * y) + x)];
		}

		auto view() noexcept
		{
			// 1. Define dynamic 2D extents
			using extents_type = std::dextents<std::size_t, 2>;

			// 2. Define the mapping type alias (This completely satisfies the MSVC parser!)
			using mapping_type = std::layout_stride::mapping<extents_type>;

			extents_type extents{ m_h, m_w };

			// 3. Define the strides
			std::array<std::size_t, 2> strides{ m_aligned_w, 1 };

			// 4. Instantiate using the alias (no confusing < > symbols here!)
			mapping_type mapping{ extents, strides };

			// 5. Bind it to raw pointer
			return std::mdspan(m_pixels.get(), mapping);
		}
	};

	template<typename PixelType>
	void saveAsPPM(const Image<PixelType>& img, const std::string& filename)
	{
		std::ofstream ofs(filename, std::ios::binary);

		// PPM Header (Pn= binary monochrome, w, h, max brightness) Mono: n=5, Colour: n=6
		if constexpr (std::same_as<PixelType, RgbaPixel>)
		{
			ofs << "P6\n";
		}
		else
		{
			ofs << "P5\n";
		}
		ofs << img.width() << " " << img.height() << " " << "\n255\n";

		for (uint32_t y = 0; y < img.height(); ++y)
		{
			for (uint32_t x = 0; x < img.width(); ++x)
			{
				if constexpr (std::same_as<PixelType, RgbaPixel>)
				{
					ofs.put(img.at(x, y).r);
					ofs.put(img.at(x, y).g);
					ofs.put(img.at(x, y).b);
				}
				else
				{
					ofs.put(img.at(x, y).intensity);
				}
			}
		}
	}

	template<typename PixelType>
	Image<PixelType> loadFromPPM(const std::string& filename)
	{
		std::ifstream ifs(filename, std::ios::binary);
		if (!ifs)
		{
			throw std::runtime_error("Failed to open golden master file: " + filename);
		}

		std::string format;
		uint32_t w = 0, h = 0, max_val = 0;

		// Header (Pn\nWidth Height\nMax_val) Mono: n=5, Color: n=6
		ifs >> format >> w >> h >> max_val;
		ifs.ignore();	// Skip CRLF

		if ((format != "P5" && format != "P6") || max_val != 255)
		{
			throw std::runtime_error("Invalid PPM format. Must be P5 and max 255.");
		}

		Image<PixelType> img(w, h);

		for (uint32_t y = 0; y < h; ++y)
		{
			for (uint32_t x = 0; x < w; ++x)
			{
				if constexpr (std::same_as<PixelType, RgbaPixel>)
				{
					img.at(x, y) = RgbaPixel
					{
						static_cast<uint8_t>(ifs.get()),
						static_cast<uint8_t>(ifs.get()),
						static_cast<uint8_t>(ifs.get()),
						255
					};
				}
				else
				{
					img.at(x, y).intensity = static_cast<uint8_t>(ifs.get());
				}
			}
		}
		return img;
	}

	template<typename PixelType>
	bool compareImages(const Image<PixelType>& actual, const Image<PixelType>& expected, double allowed_error = 0.5)
	{
		if ((actual.width() != expected.width()) ||
			(actual.height() != expected.height()))
		{
			return false;
		}

		double total_squared_error_r = 0;
		double total_squared_error_g = 0;
		double total_squared_error_b = 0;
		double total_squared_error = 0;
		uint32_t num_pixels = actual.width() * actual.height();

		for (uint32_t y = 0; y < actual.height(); ++y)
		{
			for (uint32_t x = 0; x < actual.width(); ++x)
			{
				if constexpr (std::same_as<PixelType, RgbaPixel>)
				{
					double diff = (static_cast<double>(actual.at(x, y).r) - static_cast<double>(expected.at(x, y).r));
					total_squared_error_r += diff * diff;
					diff = (static_cast<double>(actual.at(x, y).g) - static_cast<double>(expected.at(x, y).g));
					total_squared_error_g += diff * diff;
					diff = (static_cast<double>(actual.at(x, y).b) - static_cast<double>(expected.at(x, y).b));
					total_squared_error_b += diff * diff;
				}
				else
				{
					double diff = static_cast<double>(actual.at(x, y).intensity) - static_cast<double>(expected.at(x, y).intensity);
					total_squared_error += diff * diff;
				}

			}
		}

		double rmse = 0;

		if constexpr (std::same_as<PixelType, RgbaPixel>)
		{
#if true
			rmse = std::sqrt((total_squared_error_r + total_squared_error_g + total_squared_error_b) / (3 * num_pixels));
#else
			rmse = std::sqrt(total_squared_error_r / num_pixels)
				+ std::sqrt(total_squared_error_g / num_pixels)
				+ std::sqrt(total_squared_error_b / num_pixels);
#endif
		}
		else
		{
			rmse = std::sqrt(total_squared_error / num_pixels);
		}
		std::cout << "Image Diff (RMSE): " << rmse << std::endl;

		return rmse <= allowed_error;
	}


	template<typename PixelType>
	void drawDiagonalGradient(Image<PixelType>& img)
	{
		const int w = img.width();
		const int h = img.height();

		for (int y = 0; y < h; ++y)
		{
			for (int x = 0; x < w; ++x)
			{
				if constexpr (std::same_as<PixelType, RgbaPixel>)
				{
					float t = (x + y) / static_cast<float>((w - 1) + (h - 1));

					uint8_t r = static_cast<uint8_t>(255 * t);
					uint8_t g = static_cast<uint8_t>(255 * (1.0f - t));
					uint8_t b = static_cast<uint8_t>(255 * (0.5f + 0.5f * t));

					img.at(x, y) = RgbaPixel{ r, g, b, 255 };
				}
				else
				{
					img.at(x, y).intensity = static_cast<uint8_t>(std::clamp(static_cast<float>(x + y) / 2, 0.0f, 255.0f));
				}
			}
		}
	}

	template<typename PixelType>
	void drawWhiteRect(Image<PixelType>& image)
	{
		uint32_t lx = image.width() / 4;
		uint32_t rx = image.width() - lx;
		uint32_t ty = image.height() / 4;
		uint32_t by = image.height() - ty;

		for (uint32_t y = 0; y < image.height(); ++y)
		{
			for (uint32_t x = 0; x < image.width(); ++x)
			{
				if ((lx < x) && (x < rx) && (ty < y) && (y < by))
				{
					if constexpr (std::same_as<PixelType, RgbaPixel>)
					{
						image.at(x, y) = RgbaPixel{ 255, 255, 255, 255 };	// White
					}
					else
					{
						image.at(x, y) = GrayPixel{ 255 };	// White
					}
				}
				else
				{
					if constexpr (std::same_as<PixelType, RgbaPixel>)
					{
						image.at(x, y) = RgbaPixel{ (uint8_t)(x % 256), 255, 255, 255 }; // shading
					}
					else
					{
						image.at(x, y) = GrayPixel{ (uint8_t)(x % 256) }; // shading
					}
				}
			}
		}
	}

}
