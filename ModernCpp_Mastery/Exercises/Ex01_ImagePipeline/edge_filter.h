#pragma once
#include <cmath>
#include "image_filter.h"

namespace Ex01_ImagePipeline
{
	template<PixelType Pixel, Strategy S>
	class EdgeFilter : public IImageFilter<Pixel, Pixel>
	{
	public:
		using src_pixel_type = Pixel;
		using dst_pixel_type = Pixel;

		void apply(const Image<Pixel>& src, Image<Pixel>& dst) override
		{
			SliceMetadata slice(0, src.height(), src.width(), src.height());
			apply(src, dst, slice);
		}

		void apply(const Image<Pixel>& src, Image<Pixel>& dst, const SliceMetadata slice) override
		{
			if (slice.startY == 0)
			{
				// Draw top edge (copy src to dst)
				for (uint32_t x = 0; x < src.width(); ++x)
				{
					dst.at(x, 0).intensity = src.at(x, 0).intensity;	// Top edge
				}
			}
			if (slice.startY + slice.height == src.height())
			{
				// Draw bottom edge (copy src to dst)
				for (uint32_t x = 0; x < src.width(); ++x)
				{
					dst.at(x, src.height() - 1).intensity = src.at(x, src.height() - 1).intensity;	// Bottom edge
				}
			}

			uint32_t targetStartY = slice.startY == 0 ? slice.startY + 1 : slice.startY;
			uint32_t targetHeight = slice.height;
			if (slice.startY == 0)
			{
				--targetHeight; // Exclude the top scanline
			}
			if (slice.startY + slice.height == src.height())
			{
				--targetHeight;	// Exclude the bottom scanline
			}

			for (uint32_t y = 0; y < targetHeight; ++y)
			{
				dst.at(0, targetStartY + y).intensity = src.at(0, targetStartY + y).intensity;	// Left edge
				dst.at(src.width() - 1, targetStartY + y).intensity = src.at(src.width() - 1, targetStartY + y).intensity;	// Right edge
			}

			if constexpr (S == Strategy::Naive)
			{
				for (uint32_t y = 0; y < targetHeight; ++y)
				{
					for (uint32_t x = 1; x < src.width() - 1; ++x)
					{
						int32_t gx
							= src.at(x - 1, targetStartY + y - 1).intensity * -1
//							+ src.at(x, targetStartY + y - 1).intensity		*  0
							+ src.at(x + 1, targetStartY + y - 1).intensity * 1
							+ src.at(x - 1, targetStartY + y).intensity * -2
//							+ src.at(x, targetStartY + y).intensity			*  0
							+ src.at(x + 1, targetStartY + y).intensity * 2
							+ src.at(x - 1, targetStartY + y + 1).intensity * -1
//							+ src.at(x, targetStartY + y + 1).intensity		*  0
							+ src.at(x + 1, targetStartY + y + 1).intensity * 1;
						int32_t gy
							= src.at(x - 1, targetStartY + y - 1).intensity * -1
							+ src.at(x, targetStartY + y - 1).intensity * -2
							+ src.at(x + 1, targetStartY + y - 1).intensity * -1
//							+ src.at(x - 1, targetStartY + y).intensity		*  0
//							+ src.at(x, targetStartY + y).intensity			*  0
//							+ src.at(x + 1, targetStartY + y).intensity		*  0
							+src.at(x - 1, targetStartY + y + 1).intensity * 1
							+ src.at(x, targetStartY + y + 1).intensity * 2
							+ src.at(x + 1, targetStartY + y + 1).intensity * 1;
//						dst.at(x, targetStartY + y) = GrayPixel{ (uint8_t)(std::clamp(std::hypot(gx, gy), 0.0, 255.0)) };
						int32_t mag = std::abs(gx) + std::abs(gy);
						dst.at(x, targetStartY + y) = GrayPixel{ (uint8_t)(std::min(255, mag)) };
					}
				}
			}
			else
			{
				for (uint32_t y = 0; y < targetHeight; ++y)
				{
					uint32_t x = 1;
					for (; x + 16 < src.width(); x += 16)
					{
						// Load 9 positions
						__m128i t_l_8 = _mm_loadu_si128(reinterpret_cast<const __m128i*>(&src.at(x - 1, targetStartY + y - 1)));
						__m128i t_c_8 = _mm_loadu_si128(reinterpret_cast<const __m128i*>(&src.at(x, targetStartY + y - 1)));
						__m128i t_r_8 = _mm_loadu_si128(reinterpret_cast<const __m128i*>(&src.at(x + 1, targetStartY + y - 1)));
						__m128i m_l_8 = _mm_loadu_si128(reinterpret_cast<const __m128i*>(&src.at(x - 1, targetStartY + y)));
						__m128i m_c_8 = _mm_loadu_si128(reinterpret_cast<const __m128i*>(&src.at(x, targetStartY + y)));
						__m128i m_r_8 = _mm_loadu_si128(reinterpret_cast<const __m128i*>(&src.at(x + 1, targetStartY + y)));
						__m128i b_l_8 = _mm_loadu_si128(reinterpret_cast<const __m128i*>(&src.at(x - 1, targetStartY + y + 1)));
						__m128i b_c_8 = _mm_loadu_si128(reinterpret_cast<const __m128i*>(&src.at(x, targetStartY + y + 1)));
						__m128i b_r_8 = _mm_loadu_si128(reinterpret_cast<const __m128i*>(&src.at(x + 1, targetStartY + y + 1)));

						// 8 -> 16
						__m256i t_l = _mm256_cvtepu8_epi16(t_l_8);
						__m256i t_c = _mm256_cvtepu8_epi16(t_c_8);
						__m256i t_r = _mm256_cvtepu8_epi16(t_r_8);
						__m256i m_l = _mm256_cvtepu8_epi16(m_l_8);
						__m256i m_c = _mm256_cvtepu8_epi16(m_c_8);
						__m256i m_r = _mm256_cvtepu8_epi16(m_r_8);
						__m256i b_l = _mm256_cvtepu8_epi16(b_l_8);
						__m256i b_c = _mm256_cvtepu8_epi16(b_c_8);
						__m256i b_r = _mm256_cvtepu8_epi16(b_r_8);

						// gx = (t_r - t_l) + ((m_r - m_l) * 2) + (b_r - b_l)
						__m256i gx = _mm256_sub_epi16(t_r, t_l);	// (t_r - t_l)
						__m256i m_dif = _mm256_sub_epi16(m_r, m_l);	// (m_r - m_l)
						m_dif = _mm256_slli_epi16(m_dif, 1);		// (m_r - m_l) * 2
						gx = _mm256_add_epi16(gx, m_dif);			//  + ((m_r - m_l) * 2)
						__m256i b_dif = _mm256_sub_epi16(b_r, b_l);	// (b_r - b_l)
						gx = _mm256_add_epi16(gx, b_dif);			//  + (b_r - b_l)

						// gy = (b_l - t_l) + ((b_c - t_c) * 2) + (b_r - t_r)
						__m256i gy = _mm256_sub_epi16(b_l, t_l);	// (b_l - t_l)
						__m256i c_dif = _mm256_sub_epi16(b_c, t_c);	// (b_c - t_c)
						c_dif = _mm256_slli_epi16(c_dif, 1);		// (b_c - t_c) * 2
						gy = _mm256_add_epi16(gy, c_dif);			// + ((b_c - t_c) * 2)
						__m256i r_dif = _mm256_sub_epi16(b_r, t_r);	// (b_r - t_r)
						gy = _mm256_add_epi16(gy, r_dif);			// + (b_r - t_r)

						__m256i abs_gx = _mm256_abs_epi16(gx);
						__m256i abs_gy = _mm256_abs_epi16(gy);
						__m256i mag = _mm256_add_epi16(abs_gx, abs_gy);

						__m128i lo_xmm = _mm256_castsi256_si128(mag);
						__m128i hi_xmm = _mm256_extracti128_si256(mag, 1);
						__m128i packed = _mm_packus_epi16(lo_xmm, hi_xmm);

						uint8_t* d = reinterpret_cast<uint8_t*>(&dst.at(x, targetStartY + y));
						_mm_storeu_si128(reinterpret_cast<__m128i*>(d), packed);

					}
					for (; x < src.width() - 1; ++x)
					{
						// gx = (t_r - t_l) + ((m_r - m_l) * 2) + (b_r - b_l)
						int32_t gx
							= src.at(x - 1, targetStartY + y - 1).intensity * -1
							+ src.at(x + 1, targetStartY + y - 1).intensity * 1
							+ src.at(x - 1, targetStartY + y).intensity * -2
							+ src.at(x + 1, targetStartY + y).intensity * 2
							+ src.at(x - 1, targetStartY + y + 1).intensity * -1
							+ src.at(x + 1, targetStartY + y + 1).intensity * 1;
						// gy = (b_l - t_l) + ((b_c - t_c) * 2) + (b_r - t_r)
						int32_t gy
							= src.at(x - 1, targetStartY + y - 1).intensity * -1
							+ src.at(x, targetStartY + y - 1).intensity * -2
							+ src.at(x + 1, targetStartY + y - 1).intensity * -1
							+ src.at(x - 1, targetStartY + y + 1).intensity * 1
							+ src.at(x, targetStartY + y + 1).intensity * 2
							+ src.at(x + 1, targetStartY + y + 1).intensity * 1;
						int32_t mag = std::abs(gx) + std::abs(gy);
						dst.at(x, targetStartY + y) = GrayPixel{ (uint8_t)(std::min(255, mag)) };
					}

				}


			}
		}
	};
}
