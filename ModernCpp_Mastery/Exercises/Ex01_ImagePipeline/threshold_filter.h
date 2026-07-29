#pragma once
#include "image_filter.h"
#include <immintrin.h>

namespace Ex01_ImagePipeline
{
	template<PixelType Pixel, Strategy S>
	requires std::same_as<Pixel, GrayPixel>
	class ThresholdFilter : public IImageFilter<Pixel, Pixel>
	{
	private:
		uint8_t m_threshold = 0;
	public:
		using src_pixel_type = Pixel;
		using dst_pixel_type = Pixel;

		ThresholdFilter(uint8_t threshold) : m_threshold(threshold) {}
		void apply(const Image<Pixel>& src, Image<Pixel>& dst) override
		{
			SliceMetadata slice(0, src.height(), src.width(), src.height());
			apply(src, dst, slice);
		}

		void apply(const Image<Pixel>& src, Image<Pixel>& dst, const SliceMetadata slice) override
		{
			if constexpr (S == Strategy::Naive)
			{
				for (uint32_t y = 0; y < slice.height; ++y)
				{
					for (uint32_t x = 0; x < src.width(); ++x)
					{
						dst.at(x, slice.startY + y).intensity = (src.at(x, slice.startY + y).intensity >= m_threshold) ? 255 : 0;
					}
				}
			}
			else
			{
				// Set threshold and polar value (epi: Extended Packed Integer)
				__m256i t = _mm256_set1_epi8(m_threshold);				// making 8bit * 32 vector of thresholds
				__m256i v255 = _mm256_set1_epi8(static_cast<char>(255));// making 8bit * 32 vector of polar values
				__m256i v0 = _mm256_set1_epi8(static_cast<char>(0));// making 8bit * 32 vector of polar values
				__m256i u2s = _mm256_set1_epi8(static_cast<char>(0x80));// Unsigned to signed

				for (uint32_t y = 0; y < slice.height; ++y)
				{
					// The buffer is 32 bytes(32 pixels) boundaried.
					for (uint32_t x = 0; x < src.stride(); x += 32)
					{
						// Load pixels from Src to (si: Scalar Integer) register
						const __m256i* s = reinterpret_cast<const __m256i*>(&src.at(x, slice.startY + y));
						__m256i v = _mm256_loadu_si256(s);

						// Note:
						// SIMD functions accepts only signed values.
						// Convert unsigned to signed for both src and threshold values
						__m256i v_s = _mm256_xor_si256(v, u2s);
						__m256i t_s = _mm256_xor_si256(t, u2s);

						// Compare pixels with threshold in signed values
						__m256i gt = _mm256_cmpgt_epi8(v_s, t_s);	// 0xFF: GreaterEqual, 0x00: not
						__m256i eq = _mm256_cmpeq_epi8(v_s, t_s);	// 0xFF: Equal, 0x00: not
						__m256i m = _mm256_or_si256(gt, eq);		// Make results of Greater Equal

						// if (mask == 0xFF)
						//   o = 255;	only value is set where marked as 0xFF
						// else
						//   o = 0		only value is set where not marked
						__m256i o = _mm256_or_si256(		// OR the results
							_mm256_and_si256(m, v255),		// 0xFF? 255 (polar value) : 0
							_mm256_andnot_si256(m, v0));	// 0xFF? 0 : 0 (polar value)

						// Write to Dst
						__m256i* d = reinterpret_cast<__m256i*>(&dst.at(x, slice.startY + y));
						// __m256i o = _mm256_and_si256(m, v255); // simple version
						_mm256_storeu_si256(d, o);
					}
				}
			}
		}


	};
}

