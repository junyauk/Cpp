#pragma once
#include <cmath>
#include "image_filter.h"

namespace Ex01_ImagePipeline
{
	template <PixelType SrcPixel, PixelType DstPixel, Strategy S>
		requires RgbLikePixel<SrcPixel>&& std::same_as<DstPixel, GrayPixel>
	class GrayScaleFilter : public IImageFilter<SrcPixel, DstPixel>
	{
	public:
		using src_pixel_type = SrcPixel;
		using dst_pixel_type = DstPixel;

		void apply(const Image<SrcPixel>& src, Image<DstPixel>& dst) override
		{
			SliceMetadata slice(0, src.height(), src.width(), src.height());
			apply(src, dst, slice);
		}

		void apply(const Image<SrcPixel>& src, Image<DstPixel>& dst, const SliceMetadata slice) override
		{
			if constexpr (S == Strategy::Naive)
			{
				for (uint32_t y = 0; y < slice.height; ++y)
				{
					for (uint32_t x = 0; x < src.width(); ++x)
					{
						SrcPixel colour = src.at(x, slice.startY + y);
						uint32_t r = colour.r * 77;
						uint32_t g = colour.g * 150;
						uint32_t b = colour.b * 29;
						uint8_t intensity = static_cast<uint8_t>((r + g + b) >> 8);
						dst.at(x, slice.startY + y) = GrayPixel{ intensity };
					}
				}
			}
			else
			{
				const __m256i zero = _mm256_setzero_si256();
				// Make weight originally [R: 77, G: 150, B: 29]
				const RgbaPixel weights_pixel{ 77, 150, 29, 0 };
				// Note: Can't directly use RgbaPixel, convert it using std::bit_cast<int32_t>
				const int32_t packed_weight = std::bit_cast<int32_t>(weights_pixel);
				const __m256i w8 = _mm256_set1_epi32(packed_weight); // It accepts typical primitive type int32_t
				const __m256i w16 = _mm256_unpacklo_epi8(w8, zero);
				const __m128i gather_m = _mm_setr_epi8(0, 2, 4, 6, 8, 10, 12, 14, -1, -1, -1, -1, -1, -1, -1, -1);

				for (uint32_t y = 0; y < slice.height; ++y)
				{
					// The buffer is 32 bytes(8 pixels) boundaried.
					for (uint32_t x = 0; x < slice.globalWidth; x += 8)
					{
						// Get src address
						const __m256i* s = reinterpret_cast<const __m256i*>(&src.at(x, slice.startY + y));
						__m256i v = _mm256_loadu_si256(s);

						__m256i rgb_a = _mm256_unpacklo_epi8(v, zero);	// P0, P1, P4, P5
						__m256i rgb_b = _mm256_unpackhi_epi8(v, zero);	// P2, P3, P6, P7
						__m256i madd_a = _mm256_madd_epi16(rgb_a, w16);	// P0(RwGw,Bw), P1(RwGw,Bw), P4(RwGw,Bw), P5(RwGw,Bw)
						__m256i madd_b = _mm256_madd_epi16(rgb_b, w16);	// P2(RwGw,Bw), P3(RwGw,Bw), P6(RwGw,Bw), P7(RwGw,Bw)
						__m256i hadd = _mm256_hadd_epi32(madd_a, madd_b);
						__m256i pack16 = _mm256_srli_epi32(hadd, 8);	// P0(RGB), P1(RGB), duplicate, P4(RGB), P5(RGB), duplicate
						__m128i lo_xmm = _mm256_castsi256_si128(pack16);		// P0P1, P0P1, P2P3, P2P3
						__m128i hi_xmm = _mm256_extracti128_si256(pack16, 1);	// P4P5, P4P5, P6P7, P6P7

						__m128i packed_u8 = _mm_packus_epi16(lo_xmm, hi_xmm);	// P0P1P0P1, P2P3P2P3, P4P5P4P5, P6P7P6P7, duplicate
						__m128i final_bytes = _mm_shuffle_epi8(packed_u8, gather_m);	// P0P1P2P3P4P5P6

						uint32_t* d = reinterpret_cast<uint32_t*>(&dst.at(x, slice.startY + y));
						_mm_storel_epi64(reinterpret_cast<__m128i*>(d), final_bytes);

					}
				}
			}
		}
	};
}
