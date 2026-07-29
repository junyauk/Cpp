#pragma once
#include "image_filter.h"

namespace Ex01_ImagePipeline
{
	template<PixelType SrcPixel, PixelType DstPixel, Strategy S>
	requires std::same_as<SrcPixel, GrayPixel> && RgbLikePixel<DstPixel>
	class SepiaFilter : public IImageFilter<SrcPixel, DstPixel>
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
						// Gray -> RGBA
						auto& pixel = src.at(x, slice.startY + y);	// Get the target pixel
						auto r = (pixel.intensity * 173) >> 7;
						auto g = (pixel.intensity * 154) >> 7;
						auto b = (pixel.intensity * 120) >> 7;
						// Set the values as RgbaPixel
						dst.at(x, slice.startY + y) = RgbaPixel
						{
							static_cast<uint8_t>(std::clamp(r, 0, 255)),
							static_cast<uint8_t>(std::clamp(g, 0, 255)),
							static_cast<uint8_t>(std::clamp(b, 0, 255)),
							255
						};
					}
				}
			}
			else if constexpr (S == Strategy::Simd || S == Strategy::Simd1)
			{
				const __m128i zero = _mm_setzero_si128();
				const __m128i wR = _mm_set1_epi16(173);
				const __m128i wG = _mm_set1_epi16(154);
				const __m128i wB = _mm_set1_epi16(120);
				const __m128i a16 = _mm_set1_epi16(255);

				for (uint32_t y = 0; y < slice.height; ++y)
				{
					uint32_t x = 0;
					// The buffer is 32 bytes(32 pixels) boundaried.
					for (; x + 8 <= slice.globalWidth; x += 8)
					{
						// Load
						const __m128i* s = reinterpret_cast<const __m128i*>(&src.at(x, slice.startY + y));
						__m128i v = _mm_loadu_si64(s);

						// Expand 8 bytes (8 pixels) -> 16 bytes (128 bit register)
						__m128i v16 = _mm_cvtepu8_epi16(v);

						// Multiply
						__m128i r16 = _mm_mullo_epi16(v16, wR);
						__m128i g16 = _mm_mullo_epi16(v16, wG);
						__m128i b16 = _mm_mullo_epi16(v16, wB);
						// Shift (>> 7)
						r16 = _mm_srli_epi16(r16, 7);
						g16 = _mm_srli_epi16(g16, 7);
						b16 = _mm_srli_epi16(b16, 7);

						// Pair RG
						__m128i rg_lo = _mm_unpacklo_epi16(r16, g16);
						__m128i rg_hi = _mm_unpackhi_epi16(r16, g16);

						// Pair BA
						__m128i ba_lo = _mm_unpacklo_epi16(b16, a16);
						__m128i ba_hi = _mm_unpackhi_epi16(b16, a16);

						// Merge pairs
						__m128i rgba_0_1 = _mm_unpacklo_epi32(rg_lo, ba_lo);
						__m128i rgba_2_3 = _mm_unpackhi_epi32(rg_lo, ba_lo);
						__m128i rgba_4_5 = _mm_unpacklo_epi32(rg_hi, ba_hi);
						__m128i rgba_6_7 = _mm_unpackhi_epi32(rg_hi, ba_hi);

						// Combine
						__m256i rgba16_lo = _mm256_set_m128i(rgba_4_5, rgba_0_1);
						__m256i rgba16_hi = _mm256_set_m128i(rgba_6_7, rgba_2_3);

						// Saturated Pack down to 8-bit bytes
						__m256i final_rgba_256 = _mm256_packus_epi16(rgba16_lo, rgba16_hi);

						uint32_t* d = reinterpret_cast<uint32_t*>(&dst.at(x, slice.startY + y));
						_mm256_storeu_si256(reinterpret_cast<__m256i*>(d), final_rgba_256);
					}
					for (; x < src.width(); ++x)
					{
						// Gray -> RGBA
						auto& pixel = src.at(x, slice.startY + y);	// Get the target pixel
						auto r = (pixel.intensity * 173) >> 7;
						auto g = (pixel.intensity * 154) >> 7;
						auto b = (pixel.intensity * 120) >> 7;
						// Set the values as RgbaPixel
						dst.at(x, slice.startY + y) = RgbaPixel
						{
							static_cast<uint8_t>(std::clamp(r, 0, 255)),
							static_cast<uint8_t>(std::clamp(g, 0, 255)),
							static_cast<uint8_t>(std::clamp(b, 0, 255)),
							255
						};
					}
				}


			}
			else if constexpr(S == Strategy::Simd2)
			{
				const __m256i zero = _mm256_setzero_si256();
				const __m256i wR = _mm256_set1_epi16(173);
				const __m256i wG = _mm256_set1_epi16(154);
				const __m256i wB = _mm256_set1_epi16(120);
				const __m256i a16 = _mm256_set1_epi16(255);

				for (uint32_t y = 0; y < slice.height; ++y)
				{
					uint32_t x = 0;
					// The buffer is 32 bytes(32 pixels) boundaried.
					for (; x + 32 <= slice.globalWidth; x += 32)
					{
						// Get src address
						const __m256i* s = reinterpret_cast<const __m256i*>(&src.at(x, slice.startY + y));
						__m256i v = _mm256_loadu_si256(s);

						// Split 
						__m128i lo_xmm = _mm256_castsi256_si128(v);		// P0P1, P0P1, P2P3, P2P3
						__m128i hi_xmm = _mm256_extracti128_si256(v, 1);	// P4P5, P4P5, P6P7, P6P7
						__m256i v_00_15 = _mm256_cvtepu8_epi16(lo_xmm);
						__m256i v_16_31 = _mm256_cvtepu8_epi16(hi_xmm);
						// Multiply
						__m256i mulR_00_15 = _mm256_mullo_epi16(v_00_15, wR);
						__m256i mulR_16_31 = _mm256_mullo_epi16(v_16_31, wR);
						__m256i mulG_00_15 = _mm256_mullo_epi16(v_00_15, wG);
						__m256i mulG_16_31 = _mm256_mullo_epi16(v_16_31, wG);
						__m256i mulB_00_15 = _mm256_mullo_epi16(v_00_15, wB);
						__m256i mulB_16_31 = _mm256_mullo_epi16(v_16_31, wB);
						// Shift (>> 7)
						__m256i r16_00_15 = _mm256_srli_epi16(mulR_00_15, 7);
						__m256i r16_16_31 = _mm256_srli_epi16(mulR_16_31, 7);
						__m256i g16_00_15 = _mm256_srli_epi16(mulG_00_15, 7);
						__m256i g16_16_31 = _mm256_srli_epi16(mulG_16_31, 7);
						__m256i b16_00_15 = _mm256_srli_epi16(mulB_00_15, 7);
						__m256i b16_16_31 = _mm256_srli_epi16(mulB_16_31, 7);

						// Pair RG
						__m256i rg_00_15_lo = _mm256_unpacklo_epi16(r16_00_15, g16_00_15);
						__m256i rg_00_15_hi = _mm256_unpackhi_epi16(r16_00_15, g16_00_15);
						__m256i rg_16_31_lo = _mm256_unpacklo_epi16(r16_16_31, g16_16_31);
						__m256i rg_16_31_hi = _mm256_unpackhi_epi16(r16_16_31, g16_16_31);
						// Pair BA
						__m256i ba_00_15_lo = _mm256_unpacklo_epi16(b16_00_15, a16);
						__m256i ba_00_15_hi = _mm256_unpackhi_epi16(b16_00_15, a16);
						__m256i ba_16_31_lo = _mm256_unpacklo_epi16(b16_16_31, a16);
						__m256i ba_16_31_hi = _mm256_unpackhi_epi16(b16_16_31, a16);

						// Merge pairs
						__m256i rgba_a = _mm256_unpacklo_epi32(rg_00_15_lo, ba_00_15_lo);
						__m256i rgba_b = _mm256_unpackhi_epi32(rg_00_15_lo, ba_00_15_lo);
						__m256i rgba_c = _mm256_unpacklo_epi32(rg_00_15_hi, ba_00_15_hi);
						__m256i rgba_d = _mm256_unpackhi_epi32(rg_00_15_hi, ba_00_15_hi);
						__m256i rgba_e = _mm256_unpacklo_epi32(rg_16_31_lo, ba_16_31_lo);
						__m256i rgba_f = _mm256_unpackhi_epi32(rg_16_31_lo, ba_16_31_lo);
						__m256i rgba_g = _mm256_unpacklo_epi32(rg_16_31_hi, ba_16_31_hi);
						__m256i rgba_h = _mm256_unpackhi_epi32(rg_16_31_hi, ba_16_31_hi);

						// Pack (16 bit -> 8 bit)
						__m256i pack_ab = _mm256_packus_epi16(rgba_a, rgba_b);
						__m256i pack_cd = _mm256_packus_epi16(rgba_c, rgba_d);
						__m256i pack_ef = _mm256_packus_epi16(rgba_e, rgba_f);
						__m256i pack_gh = _mm256_packus_epi16(rgba_g, rgba_h);

						__m256i p00_07 = _mm256_permute2x128_si256(pack_ab, pack_cd, 0x20);
						__m256i p08_15 = _mm256_permute2x128_si256(pack_ab, pack_cd, 0x31);
						__m256i p16_23 = _mm256_permute2x128_si256(pack_ef, pack_gh, 0x20);
						__m256i p24_31 = _mm256_permute2x128_si256(pack_ef, pack_gh, 0x31);

						uint8_t* d = reinterpret_cast<uint8_t*>(&dst.at(x, slice.startY + y));
						_mm256_storeu_si256(reinterpret_cast<__m256i*>(d), p00_07);
						_mm256_storeu_si256(reinterpret_cast<__m256i*>(d+32), p08_15);
						_mm256_storeu_si256(reinterpret_cast<__m256i*>(d+64), p16_23);
						_mm256_storeu_si256(reinterpret_cast<__m256i*>(d+96), p24_31);
					}

					for (; x < src.width(); ++x)
					{
						// Gray -> RGBA
						auto& pixel = src.at(x, slice.startY + y);	// Get the target pixel
						auto r = (pixel.intensity * 173) >> 7;
						auto g = (pixel.intensity * 154) >> 7;
						auto b = (pixel.intensity * 120) >> 7;
						// Set the values as RgbaPixel
						dst.at(x, slice.startY + y) = RgbaPixel
						{
							static_cast<uint8_t>(std::clamp(r, 0, 255)),
							static_cast<uint8_t>(std::clamp(g, 0, 255)),
							static_cast<uint8_t>(std::clamp(b, 0, 255)),
							255
						};
					}


				}

			}
		}
	};


}

