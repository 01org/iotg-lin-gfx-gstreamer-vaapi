# sources.frag - Generated list of source files for libvpx (-*- makefile -*-)
#
# Copyright (C) 2014 Intel Corporation
#   Author: Gwenole Beauchesne <gwenole.beauchesne@intel.com>
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Library General Public
# License as published by the Free Software Foundation; either
# version 2 of the License, or (at your option) any later version.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Library General Public License for more details.
#
# You should have received a copy of the GNU Library General Public
# License along with this library; if not, write to the
# Free Software Foundation, Inc., 51 Franklin St, Fifth Floor,
# Boston, MA 02110-1301, USA.

vpx_source_mak = \
	build/make/Android.mk \
	docs.mk \
	examples.mk \
	libs.mk \
	solution.mk \
	test/android/Android.mk \
	test/test-data.mk \
	test/test.mk \
	third_party/googletest/gtest.mk \
	third_party/libwebm/Android.mk \
	vp8/vp8_common.mk \
	vp8/vp8cx_arm.mk \
	vp8/vp8cx.mk \
	vp8/vp8dx.mk \
	vp9/vp9_common.mk \
	vp9/vp9cx.mk \
	vp9/vp9dx.mk \
	vpx_mem/vpx_mem.mk \
	vpx_ports/vpx_ports.mk \
	vpx_scale/vpx_scale.mk \
	vpx/vpx_codec.mk \
	$(NULL)

vpx_source_c = \
	args.c \
	examples/decode_to_md5.c \
	examples/decode_with_drops.c \
	examples/postproc.c \
	examples/resize_util.c \
	examples/set_maps.c \
	examples/simple_decoder.c \
	examples/simple_encoder.c \
	examples/twopass_encoder.c \
	examples/vp8cx_set_ref.c \
	examples/vp8_multi_resolution_encoder.c \
	examples/vp9_lossless_encoder.c \
	examples/vp9_spatial_svc_encoder.c \
	examples/vpx_temporal_svc_encoder.c \
	ivfdec.c \
	ivfenc.c \
	md5_utils.c \
	rate_hist.c \
	tools_common.c \
	video_reader.c \
	video_writer.c \
	vp8/common/alloccommon.c \
	vp8/common/arm/armv6/idct_blk_v6.c \
	vp8/common/arm/bilinearfilter_arm.c \
	vp8/common/arm/dequantize_arm.c \
	vp8/common/arm/filter_arm.c \
	vp8/common/arm/loopfilter_arm.c \
	vp8/common/arm/neon/bilinearpredict_neon.c \
	vp8/common/arm/neon/copymem_neon.c \
	vp8/common/arm/neon/dc_only_idct_add_neon.c \
	vp8/common/arm/neon/dequant_idct_neon.c \
	vp8/common/arm/neon/dequantizeb_neon.c \
	vp8/common/arm/neon/idct_blk_neon.c \
	vp8/common/arm/neon/idct_dequant_0_2x_neon.c \
	vp8/common/arm/neon/idct_dequant_full_2x_neon.c \
	vp8/common/arm/neon/iwalsh_neon.c \
	vp8/common/arm/neon/loopfilter_neon.c \
	vp8/common/arm/neon/loopfiltersimplehorizontaledge_neon.c \
	vp8/common/arm/neon/loopfiltersimpleverticaledge_neon.c \
	vp8/common/arm/neon/mbloopfilter_neon.c \
	vp8/common/arm/neon/reconintra_neon.c \
	vp8/common/arm/neon/sad_neon.c \
	vp8/common/arm/neon/shortidct4x4llm_neon.c \
	vp8/common/arm/neon/sixtappredict_neon.c \
	vp8/common/arm/neon/variance_neon.c \
	vp8/common/arm/neon/vp8_subpixelvariance_neon.c \
	vp8/common/arm/variance_arm.c \
	vp8/common/blockd.c \
	vp8/common/context.c \
	vp8/common/debugmodes.c \
	vp8/common/dequantize.c \
	vp8/common/entropy.c \
	vp8/common/entropymode.c \
	vp8/common/entropymv.c \
	vp8/common/extend.c \
	vp8/common/filter.c \
	vp8/common/findnearmv.c \
	vp8/common/generic/systemdependent.c \
	vp8/common/idct_blk.c \
	vp8/common/idctllm.c \
	vp8/common/loopfilter.c \
	vp8/common/loopfilter_filters.c \
	vp8/common/mbpitch.c \
	vp8/common/mfqe.c \
	vp8/common/mips/dspr2/dequantize_dspr2.c \
	vp8/common/mips/dspr2/filter_dspr2.c \
	vp8/common/mips/dspr2/idct_blk_dspr2.c \
	vp8/common/mips/dspr2/idctllm_dspr2.c \
	vp8/common/mips/dspr2/loopfilter_filters_dspr2.c \
	vp8/common/mips/dspr2/reconinter_dspr2.c \
	vp8/common/modecont.c \
	vp8/common/postproc.c \
	vp8/common/ppc/loopfilter_altivec.c \
	vp8/common/ppc/systemdependent.c \
	vp8/common/quant_common.c \
	vp8/common/reconinter.c \
	vp8/common/reconintra4x4.c \
	vp8/common/reconintra.c \
	vp8/common/rtcd.c \
	vp8/common/sad_c.c \
	vp8/common/setupintrarecon.c \
	vp8/common/swapyv12buffer.c \
	vp8/common/textblit.c \
	vp8/common/treecoder.c \
	vp8/common/variance_c.c \
	vp8/common/x86/filter_x86.c \
	vp8/common/x86/idct_blk_mmx.c \
	vp8/common/x86/idct_blk_sse2.c \
	vp8/common/x86/loopfilter_x86.c \
	vp8/common/x86/recon_wrapper_sse2.c \
	vp8/common/x86/variance_mmx.c \
	vp8/common/x86/variance_sse2.c \
	vp8/common/x86/variance_ssse3.c \
	vp8/common/x86/vp8_asm_stubs.c \
	vp8/decoder/dboolhuff.c \
	vp8/decoder/decodeframe.c \
	vp8/decoder/decodemv.c \
	vp8/decoder/detokenize.c \
	vp8/decoder/error_concealment.c \
	vp8/decoder/onyxd_if.c \
	vp8/decoder/threading.c \
	vp8/encoder/arm/dct_arm.c \
	vp8/encoder/arm/neon/denoising_neon.c \
	vp8/encoder/arm/neon/fastquantizeb_neon.c \
	vp8/encoder/arm/neon/shortfdct_neon.c \
	vp8/encoder/arm/neon/subtract_neon.c \
	vp8/encoder/arm/neon/vp8_mse16x16_neon.c \
	vp8/encoder/arm/neon/vp8_shortwalsh4x4_neon.c \
	vp8/encoder/bitstream.c \
	vp8/encoder/boolhuff.c \
	vp8/encoder/dct.c \
	vp8/encoder/denoising.c \
	vp8/encoder/encodeframe.c \
	vp8/encoder/encodeintra.c \
	vp8/encoder/encodemb.c \
	vp8/encoder/encodemv.c \
	vp8/encoder/ethreading.c \
	vp8/encoder/firstpass.c \
	vp8/encoder/lookahead.c \
	vp8/encoder/mcomp.c \
	vp8/encoder/modecosts.c \
	vp8/encoder/mr_dissim.c \
	vp8/encoder/onyx_if.c \
	vp8/encoder/pickinter.c \
	vp8/encoder/picklpf.c \
	vp8/encoder/ppc/csystemdependent.c \
	vp8/encoder/quantize.c \
	vp8/encoder/ratectrl.c \
	vp8/encoder/rdopt.c \
	vp8/encoder/segmentation.c \
	vp8/encoder/ssim.c \
	vp8/encoder/temporal_filter.c \
	vp8/encoder/tokenize.c \
	vp8/encoder/treewriter.c \
	vp8/encoder/x86/denoising_sse2.c \
	vp8/encoder/x86/quantize_sse2.c \
	vp8/encoder/x86/quantize_sse4.c \
	vp8/encoder/x86/quantize_ssse3.c \
	vp8/encoder/x86/vp8_enc_stubs_mmx.c \
	vp8/encoder/x86/vp8_enc_stubs_sse2.c \
	vp8/vp8_cx_iface.c \
	vp8/vp8_dx_iface.c \
	vp9/common/arm/neon/vp9_avg_neon.c \
	vp9/common/arm/neon/vp9_convolve8_avg_neon.c \
	vp9/common/arm/neon/vp9_convolve8_neon.c \
	vp9/common/arm/neon/vp9_convolve_neon.c \
	vp9/common/arm/neon/vp9_copy_neon.c \
	vp9/common/arm/neon/vp9_idct16x16_1_add_neon.c \
	vp9/common/arm/neon/vp9_idct16x16_add_neon.c \
	vp9/common/arm/neon/vp9_idct16x16_neon.c \
	vp9/common/arm/neon/vp9_idct32x32_1_add_neon.c \
	vp9/common/arm/neon/vp9_idct32x32_add_neon.c \
	vp9/common/arm/neon/vp9_idct4x4_1_add_neon.c \
	vp9/common/arm/neon/vp9_idct4x4_add_neon.c \
	vp9/common/arm/neon/vp9_idct8x8_1_add_neon.c \
	vp9/common/arm/neon/vp9_idct8x8_add_neon.c \
	vp9/common/arm/neon/vp9_iht4x4_add_neon.c \
	vp9/common/arm/neon/vp9_iht8x8_add_neon.c \
	vp9/common/arm/neon/vp9_loopfilter_16_neon.c \
	vp9/common/arm/neon/vp9_loopfilter_4_neon.c \
	vp9/common/arm/neon/vp9_loopfilter_8_neon.c \
	vp9/common/arm/neon/vp9_loopfilter_neon.c \
	vp9/common/arm/neon/vp9_reconintra_neon.c \
	vp9/common/mips/dspr2/vp9_convolve2_avg_dspr2.c \
	vp9/common/mips/dspr2/vp9_convolve2_avg_horiz_dspr2.c \
	vp9/common/mips/dspr2/vp9_convolve2_dspr2.c \
	vp9/common/mips/dspr2/vp9_convolve2_horiz_dspr2.c \
	vp9/common/mips/dspr2/vp9_convolve2_vert_dspr2.c \
	vp9/common/mips/dspr2/vp9_convolve8_avg_dspr2.c \
	vp9/common/mips/dspr2/vp9_convolve8_avg_horiz_dspr2.c \
	vp9/common/mips/dspr2/vp9_convolve8_dspr2.c \
	vp9/common/mips/dspr2/vp9_convolve8_horiz_dspr2.c \
	vp9/common/mips/dspr2/vp9_convolve8_vert_dspr2.c \
	vp9/common/mips/dspr2/vp9_intrapred16_dspr2.c \
	vp9/common/mips/dspr2/vp9_intrapred4_dspr2.c \
	vp9/common/mips/dspr2/vp9_intrapred8_dspr2.c \
	vp9/common/mips/dspr2/vp9_itrans16_dspr2.c \
	vp9/common/mips/dspr2/vp9_itrans32_cols_dspr2.c \
	vp9/common/mips/dspr2/vp9_itrans32_dspr2.c \
	vp9/common/mips/dspr2/vp9_itrans4_dspr2.c \
	vp9/common/mips/dspr2/vp9_itrans8_dspr2.c \
	vp9/common/mips/dspr2/vp9_loopfilter_filters_dspr2.c \
	vp9/common/mips/dspr2/vp9_mbloop_loopfilter_dspr2.c \
	vp9/common/mips/dspr2/vp9_mblpf_horiz_loopfilter_dspr2.c \
	vp9/common/mips/dspr2/vp9_mblpf_vert_loopfilter_dspr2.c \
	vp9/common/vp9_alloccommon.c \
	vp9/common/vp9_blockd.c \
	vp9/common/vp9_common_data.c \
	vp9/common/vp9_convolve.c \
	vp9/common/vp9_debugmodes.c \
	vp9/common/vp9_entropy.c \
	vp9/common/vp9_entropymode.c \
	vp9/common/vp9_entropymv.c \
	vp9/common/vp9_filter.c \
	vp9/common/vp9_frame_buffers.c \
	vp9/common/vp9_idct.c \
	vp9/common/vp9_loopfilter.c \
	vp9/common/vp9_loopfilter_filters.c \
	vp9/common/vp9_mfqe.c \
	vp9/common/vp9_mvref_common.c \
	vp9/common/vp9_postproc.c \
	vp9/common/vp9_pred_common.c \
	vp9/common/vp9_prob.c \
	vp9/common/vp9_quant_common.c \
	vp9/common/vp9_reconinter.c \
	vp9/common/vp9_reconintra.c \
	vp9/common/vp9_rtcd.c \
	vp9/common/vp9_scale.c \
	vp9/common/vp9_scan.c \
	vp9/common/vp9_seg_common.c \
	vp9/common/vp9_textblit.c \
	vp9/common/vp9_thread.c \
	vp9/common/vp9_thread_common.c \
	vp9/common/vp9_tile_common.c \
	vp9/common/x86/vp9_asm_stubs.c \
	vp9/common/x86/vp9_high_loopfilter_intrin_sse2.c \
	vp9/common/x86/vp9_idct_intrin_sse2.c \
	vp9/common/x86/vp9_idct_intrin_ssse3.c \
	vp9/common/x86/vp9_loopfilter_intrin_avx2.c \
	vp9/common/x86/vp9_loopfilter_intrin_sse2.c \
	vp9/common/x86/vp9_subpixel_8t_intrin_avx2.c \
	vp9/common/x86/vp9_subpixel_8t_intrin_ssse3.c \
	vp9/decoder/vp9_decodeframe.c \
	vp9/decoder/vp9_decodemv.c \
	vp9/decoder/vp9_decoder.c \
	vp9/decoder/vp9_detokenize.c \
	vp9/decoder/vp9_dsubexp.c \
	vp9/decoder/vp9_dthread.c \
	vp9/decoder/vp9_read_bit_buffer.c \
	vp9/decoder/vp9_reader.c \
	vp9/encoder/arm/neon/vp9_avg_neon.c \
	vp9/encoder/arm/neon/vp9_dct_neon.c \
	vp9/encoder/arm/neon/vp9_quantize_neon.c \
	vp9/encoder/arm/neon/vp9_sad4d_neon.c \
	vp9/encoder/arm/neon/vp9_sad_neon.c \
	vp9/encoder/arm/neon/vp9_subtract_neon.c \
	vp9/encoder/arm/neon/vp9_variance_neon.c \
	vp9/encoder/vp9_aq_complexity.c \
	vp9/encoder/vp9_aq_cyclicrefresh.c \
	vp9/encoder/vp9_aq_variance.c \
	vp9/encoder/vp9_avg.c \
	vp9/encoder/vp9_bitstream.c \
	vp9/encoder/vp9_context_tree.c \
	vp9/encoder/vp9_cost.c \
	vp9/encoder/vp9_dct.c \
	vp9/encoder/vp9_denoiser.c \
	vp9/encoder/vp9_encodeframe.c \
	vp9/encoder/vp9_encodemb.c \
	vp9/encoder/vp9_encodemv.c \
	vp9/encoder/vp9_encoder.c \
	vp9/encoder/vp9_ethread.c \
	vp9/encoder/vp9_extend.c \
	vp9/encoder/vp9_firstpass.c \
	vp9/encoder/vp9_lookahead.c \
	vp9/encoder/vp9_mbgraph.c \
	vp9/encoder/vp9_mcomp.c \
	vp9/encoder/vp9_picklpf.c \
	vp9/encoder/vp9_pickmode.c \
	vp9/encoder/vp9_quantize.c \
	vp9/encoder/vp9_ratectrl.c \
	vp9/encoder/vp9_rd.c \
	vp9/encoder/vp9_rdopt.c \
	vp9/encoder/vp9_resize.c \
	vp9/encoder/vp9_sad.c \
	vp9/encoder/vp9_segmentation.c \
	vp9/encoder/vp9_skin_detection.c \
	vp9/encoder/vp9_speed_features.c \
	vp9/encoder/vp9_ssim.c \
	vp9/encoder/vp9_subexp.c \
	vp9/encoder/vp9_svc_layercontext.c \
	vp9/encoder/vp9_temporal_filter.c \
	vp9/encoder/vp9_tokenize.c \
	vp9/encoder/vp9_treewriter.c \
	vp9/encoder/vp9_variance.c \
	vp9/encoder/vp9_write_bit_buffer.c \
	vp9/encoder/vp9_writer.c \
	vp9/encoder/x86/vp9_avg_intrin_sse2.c \
	vp9/encoder/x86/vp9_dct32x32_avx2.c \
	vp9/encoder/x86/vp9_dct32x32_sse2.c \
	vp9/encoder/x86/vp9_dct_avx2.c \
	vp9/encoder/x86/vp9_dct_impl_sse2.c \
	vp9/encoder/x86/vp9_dct_sse2.c \
	vp9/encoder/x86/vp9_dct_ssse3.c \
	vp9/encoder/x86/vp9_denoiser_sse2.c \
	vp9/encoder/x86/vp9_error_intrin_avx2.c \
	vp9/encoder/x86/vp9_highbd_block_error_intrin_sse2.c \
	vp9/encoder/x86/vp9_highbd_quantize_intrin_sse2.c \
	vp9/encoder/x86/vp9_highbd_variance_sse2.c \
	vp9/encoder/x86/vp9_quantize_sse2.c \
	vp9/encoder/x86/vp9_sad4d_intrin_avx2.c \
	vp9/encoder/x86/vp9_sad_intrin_avx2.c \
	vp9/encoder/x86/vp9_subpel_variance_impl_intrin_avx2.c \
	vp9/encoder/x86/vp9_variance_avx2.c \
	vp9/encoder/x86/vp9_variance_impl_intrin_avx2.c \
	vp9/encoder/x86/vp9_variance_sse2.c \
	vp9/vp9_cx_iface.c \
	vp9/vp9_dx_iface.c \
	vpxdec.c \
	vpxenc.c \
	vpx_mem/memory_manager/hmm_alloc.c \
	vpx_mem/memory_manager/hmm_base.c \
	vpx_mem/memory_manager/hmm_dflt_abort.c \
	vpx_mem/memory_manager/hmm_grow.c \
	vpx_mem/memory_manager/hmm_largest.c \
	vpx_mem/memory_manager/hmm_resize.c \
	vpx_mem/memory_manager/hmm_shrink.c \
	vpx_mem/memory_manager/hmm_true.c \
	vpx_mem/vpx_mem.c \
	vpx_mem/vpx_mem_tracker.c \
	vpx_ports/arm_cpudetect.c \
	vpx_scale/generic/gen_scalers.c \
	vpx_scale/generic/vpx_scale.c \
	vpx_scale/generic/yv12config.c \
	vpx_scale/generic/yv12extend.c \
	vpx_scale/mips/dspr2/yv12extend_dspr2.c \
	vpx_scale/vpx_scale_rtcd.c \
	vpx_scale/win32/scaleopt.c \
	vpx/src/svc_encodeframe.c \
	vpx/src/vpx_codec.c \
	vpx/src/vpx_decoder.c \
	vpx/src/vpx_encoder.c \
	vpx/src/vpx_image.c \
	vpx/src/vpx_psnr.c \
	vpxstats.c \
	warnings.c \
	y4menc.c \
	y4minput.c \
	$(NULL)

vpx_source_h = \
	args.h \
	ivfdec.h \
	ivfenc.h \
	md5_utils.h \
	rate_hist.h \
	vp8_rtcd.h \
	test/acm_random.h \
	test/clear_system_state.h \
	test/codec_factory.h \
	test/decode_test_driver.h \
	test/encode_test_driver.h \
	test/i420_video_source.h \
	test/ivf_video_source.h \
	test/md5_helper.h \
	test/register_state_check.h \
	test/test_vectors.h \
	test/util.h \
	test/video_source.h \
	test/webm_video_source.h \
	test/y4m_video_source.h \
	test/yuv_video_source.h \
	third_party/googletest/src/include/gtest/gtest.h \
	third_party/libyuv/include/libyuv/basic_types.h \
	third_party/libyuv/include/libyuv/compare.h \
	third_party/libyuv/include/libyuv/convert_argb.h \
	third_party/libyuv/include/libyuv/convert_from_argb.h \
	third_party/libyuv/include/libyuv/convert_from.h \
	third_party/libyuv/include/libyuv/convert.h \
	third_party/libyuv/include/libyuv/cpu_id.h \
	third_party/libyuv/include/libyuv/mjpeg_decoder.h \
	third_party/libyuv/include/libyuv/planar_functions.h \
	third_party/libyuv/include/libyuv/rotate_argb.h \
	third_party/libyuv/include/libyuv/rotate.h \
	third_party/libyuv/include/libyuv/row.h \
	third_party/libyuv/include/libyuv/scale_argb.h \
	third_party/libyuv/include/libyuv/scale.h \
	third_party/libyuv/include/libyuv/scale_row.h \
	third_party/libyuv/include/libyuv/version.h \
	third_party/libyuv/include/libyuv/video_common.h \
	tools_common.h \
	video_common.h \
	video_reader.h \
	video_writer.h \
	vp8/common/alloccommon.h \
	vp8/common/arm/bilinearfilter_arm.h \
	vp8/common/blockd.h \
	vp8/common/coefupdateprobs.h \
	vp8/common/common.h \
	vp8/common/default_coef_probs.h \
	vp8/common/entropy.h \
	vp8/common/entropymode.h \
	vp8/common/entropymv.h \
	vp8/common/extend.h \
	vp8/common/filter.h \
	vp8/common/findnearmv.h \
	vp8/common/header.h \
	vp8/common/invtrans.h \
	vp8/common/loopfilter.h \
	vp8/common/modecont.h \
	vp8/common/mv.h \
	vp8/common/onyxc_int.h \
	vp8/common/onyxd.h \
	vp8/common/onyx.h \
	vp8/common/postproc.h \
	vp8/common/ppflags.h \
	vp8/common/quant_common.h \
	vp8/common/reconinter.h \
	vp8/common/reconintra4x4.h \
	vp8/common/setupintrarecon.h \
	vp8/common/swapyv12buffer.h \
	vp8/common/systemdependent.h \
	vp8/common/threading.h \
	vp8/common/treecoder.h \
	vp8/common/variance.h \
	vp8/common/vp8_entropymodedata.h \
	vp8/common/x86/filter_x86.h \
	vp8/decoder/dboolhuff.h \
	vp8/decoder/decodemv.h \
	vp8/decoder/decoderthreading.h \
	vp8/decoder/detokenize.h \
	vp8/decoder/ec_types.h \
	vp8/decoder/error_concealment.h \
	vp8/decoder/onyxd_int.h \
	vp8/decoder/treereader.h \
	vp8/encoder/bitstream.h \
	vp8/encoder/block.h \
	vp8/encoder/boolhuff.h \
	vp8/encoder/dct_value_cost.h \
	vp8/encoder/dct_value_tokens.h \
	vp8/encoder/defaultcoefcounts.h \
	vp8/encoder/denoising.h \
	vp8/encoder/encodeframe.h \
	vp8/encoder/encodeintra.h \
	vp8/encoder/encodemb.h \
	vp8/encoder/encodemv.h \
	vp8/encoder/firstpass.h \
	vp8/encoder/lookahead.h \
	vp8/encoder/mcomp.h \
	vp8/encoder/modecosts.h \
	vp8/encoder/mr_dissim.h \
	vp8/encoder/onyx_int.h \
	vp8/encoder/pickinter.h \
	vp8/encoder/quantize.h \
	vp8/encoder/ratectrl.h \
	vp8/encoder/rdopt.h \
	vp8/encoder/segmentation.h \
	vp8/encoder/tokenize.h \
	vp8/encoder/treewriter.h \
	vp9/common/mips/dspr2/vp9_common_dspr2.h \
	vp9/common/mips/dspr2/vp9_loopfilter_filters_dspr2.h \
	vp9/common/mips/dspr2/vp9_loopfilter_macros_dspr2.h \
	vp9/common/mips/dspr2/vp9_loopfilter_masks_dspr2.h \
	vp9/common/vp9_alloccommon.h \
	vp9/common/vp9_blockd.h \
	vp9/common/vp9_common_data.h \
	vp9/common/vp9_common.h \
	vp9/common/vp9_convolve.h \
	vp9/common/vp9_entropy.h \
	vp9/common/vp9_entropymode.h \
	vp9/common/vp9_entropymv.h \
	vp9/common/vp9_enums.h \
	vp9/common/vp9_filter.h \
	vp9/common/vp9_frame_buffers.h \
	vp9/common/vp9_idct.h \
	vp9/common/vp9_loopfilter.h \
	vp9/common/vp9_mfqe.h \
	vp9/common/vp9_mv.h \
	vp9/common/vp9_mvref_common.h \
	vp9/common/vp9_onyxc_int.h \
	vp9/common/vp9_postproc.h \
	vp9/common/vp9_ppflags.h \
	vp9/common/vp9_pred_common.h \
	vp9/common/vp9_prob.h \
	vp9/common/vp9_quant_common.h \
	vp9/common/vp9_reconinter.h \
	vp9/common/vp9_reconintra.h \
	vp9/common/vp9_scale.h \
	vp9/common/vp9_scan.h \
	vp9/common/vp9_seg_common.h \
	vp9/common/vp9_systemdependent.h \
	vp9/common/vp9_textblit.h \
	vp9/common/vp9_thread_common.h \
	vp9/common/vp9_thread.h \
	vp9/common/vp9_tile_common.h \
	vp9/common/x86/vp9_idct_intrin_sse2.h \
	vp9/decoder/vp9_decodeframe.h \
	vp9/decoder/vp9_decodemv.h \
	vp9/decoder/vp9_decoder.h \
	vp9/decoder/vp9_detokenize.h \
	vp9/decoder/vp9_dsubexp.h \
	vp9/decoder/vp9_dthread.h \
	vp9/decoder/vp9_read_bit_buffer.h \
	vp9/decoder/vp9_reader.h \
	vp9/encoder/vp9_aq_complexity.h \
	vp9/encoder/vp9_aq_cyclicrefresh.h \
	vp9/encoder/vp9_aq_variance.h \
	vp9/encoder/vp9_bitstream.h \
	vp9/encoder/vp9_block.h \
	vp9/encoder/vp9_context_tree.h \
	vp9/encoder/vp9_cost.h \
	vp9/encoder/vp9_dct.h \
	vp9/encoder/vp9_denoiser.h \
	vp9/encoder/vp9_encodeframe.h \
	vp9/encoder/vp9_encodemb.h \
	vp9/encoder/vp9_encodemv.h \
	vp9/encoder/vp9_encoder.h \
	vp9/encoder/vp9_ethread.h \
	vp9/encoder/vp9_extend.h \
	vp9/encoder/vp9_firstpass.h \
	vp9/encoder/vp9_lookahead.h \
	vp9/encoder/vp9_mbgraph.h \
	vp9/encoder/vp9_mcomp.h \
	vp9/encoder/vp9_picklpf.h \
	vp9/encoder/vp9_pickmode.h \
	vp9/encoder/vp9_quantize.h \
	vp9/encoder/vp9_ratectrl.h \
	vp9/encoder/vp9_rd.h \
	vp9/encoder/vp9_rdopt.h \
	vp9/encoder/vp9_resize.h \
	vp9/encoder/vp9_segmentation.h \
	vp9/encoder/vp9_skin_detection.h \
	vp9/encoder/vp9_speed_features.h \
	vp9/encoder/vp9_ssim.h \
	vp9/encoder/vp9_subexp.h \
	vp9/encoder/vp9_svc_layercontext.h \
	vp9/encoder/vp9_temporal_filter.h \
	vp9/encoder/vp9_tokenize.h \
	vp9/encoder/vp9_treewriter.h \
	vp9/encoder/vp9_variance.h \
	vp9/encoder/vp9_write_bit_buffer.h \
	vp9/encoder/vp9_writer.h \
	vp9/encoder/x86/vp9_dct_sse2.h \
	vp9/vp9_iface_common.h \
	vpxenc.h \
	vpx/internal/vpx_codec_internal.h \
	vpx/internal/vpx_psnr.h \
	vpx_mem/include/vpx_mem_intrnl.h \
	vpx_mem/include/vpx_mem_tracker.h \
	vpx_mem/memory_manager/include/cavl_if.h \
	vpx_mem/memory_manager/include/cavl_impl.h \
	vpx_mem/memory_manager/include/heapmm.h \
	vpx_mem/memory_manager/include/hmm_cnfg.h \
	vpx_mem/memory_manager/include/hmm_intrnl.h \
	vpx_mem/vpx_mem.h \
	vpx_ports/arm.h \
	vpx_ports/config.h \
	vpx_ports/emmintrin_compat.h \
	vpx_ports/mem.h \
	vpx_ports/mem_ops_aligned.h \
	vpx_ports/mem_ops.h \
	vpx_ports/vpx_once.h \
	vpx_ports/vpx_timer.h \
	vpx_ports/x86.h \
	vpx_scale/vpx_scale.h \
	vpx_scale/yv12config.h \
	vpxstats.h \
	vpx/svc_context.h \
	vpx/vp8cx.h \
	vpx/vp8dx.h \
	vpx/vp8.h \
	vpx/vpx_codec.h \
	vpx/vpx_decoder.h \
	vpx/vpx_encoder.h \
	vpx/vpx_frame_buffer.h \
	vpx/vpx_image.h \
	vpx/vpx_integer.h \
	vpx_scale_rtcd.h \
	warnings.h \
	webmdec.h \
	webmenc.h \
	y4menc.h \
	y4minput.h \
	$(NULL)

vpx_source_asm = \
	third_party/libyuv/source/row_x86.asm \
	third_party/libyuv/source/x86inc.asm \
	third_party/x86inc/x86inc.asm \
	vp8/common/arm/armv6/bilinearfilter_v6.asm \
	vp8/common/arm/armv6/copymem16x16_v6.asm \
	vp8/common/arm/armv6/copymem8x4_v6.asm \
	vp8/common/arm/armv6/copymem8x8_v6.asm \
	vp8/common/arm/armv6/dc_only_idct_add_v6.asm \
	vp8/common/arm/armv6/dequant_idct_v6.asm \
	vp8/common/arm/armv6/dequantize_v6.asm \
	vp8/common/arm/armv6/filter_v6.asm \
	vp8/common/arm/armv6/idct_v6.asm \
	vp8/common/arm/armv6/intra4x4_predict_v6.asm \
	vp8/common/arm/armv6/iwalsh_v6.asm \
	vp8/common/arm/armv6/loopfilter_v6.asm \
	vp8/common/arm/armv6/simpleloopfilter_v6.asm \
	vp8/common/arm/armv6/sixtappredict8x4_v6.asm \
	vp8/common/arm/armv6/vp8_sad16x16_armv6.asm \
	vp8/common/arm/armv6/vp8_variance16x16_armv6.asm \
	vp8/common/arm/armv6/vp8_variance8x8_armv6.asm \
	vp8/common/arm/armv6/vp8_variance_halfpixvar16x16_h_armv6.asm \
	vp8/common/arm/armv6/vp8_variance_halfpixvar16x16_hv_armv6.asm \
	vp8/common/arm/armv6/vp8_variance_halfpixvar16x16_v_armv6.asm \
	vp8/common/ppc/copy_altivec.asm \
	vp8/common/ppc/filter_altivec.asm \
	vp8/common/ppc/filter_bilinear_altivec.asm \
	vp8/common/ppc/idctllm_altivec.asm \
	vp8/common/ppc/loopfilter_filters_altivec.asm \
	vp8/common/ppc/platform_altivec.asm \
	vp8/common/ppc/recon_altivec.asm \
	vp8/common/ppc/sad_altivec.asm \
	vp8/common/ppc/variance_altivec.asm \
	vp8/common/ppc/variance_subpixel_altivec.asm \
	vp8/common/x86/dequantize_mmx.asm \
	vp8/common/x86/idctllm_mmx.asm \
	vp8/common/x86/idctllm_sse2.asm \
	vp8/common/x86/iwalsh_mmx.asm \
	vp8/common/x86/iwalsh_sse2.asm \
	vp8/common/x86/loopfilter_block_sse2_x86_64.asm \
	vp8/common/x86/loopfilter_mmx.asm \
	vp8/common/x86/loopfilter_sse2.asm \
	vp8/common/x86/mfqe_sse2.asm \
	vp8/common/x86/postproc_mmx.asm \
	vp8/common/x86/postproc_sse2.asm \
	vp8/common/x86/recon_mmx.asm \
	vp8/common/x86/recon_sse2.asm \
	vp8/common/x86/sad_mmx.asm \
	vp8/common/x86/sad_sse2.asm \
	vp8/common/x86/sad_sse3.asm \
	vp8/common/x86/sad_sse4.asm \
	vp8/common/x86/sad_ssse3.asm \
	vp8/common/x86/subpixel_mmx.asm \
	vp8/common/x86/subpixel_sse2.asm \
	vp8/common/x86/subpixel_ssse3.asm \
	vp8/common/x86/variance_impl_mmx.asm \
	vp8/common/x86/variance_impl_sse2.asm \
	vp8/common/x86/variance_impl_ssse3.asm \
	vp8/encoder/arm/armv6/vp8_mse16x16_armv6.asm \
	vp8/encoder/arm/armv6/vp8_short_fdct4x4_armv6.asm \
	vp8/encoder/arm/armv6/walsh_v6.asm \
	vp8/encoder/ppc/encodemb_altivec.asm \
	vp8/encoder/ppc/fdct_altivec.asm \
	vp8/encoder/ppc/rdopt_altivec.asm \
	vp8/encoder/x86/dct_mmx.asm \
	vp8/encoder/x86/dct_sse2.asm \
	vp8/encoder/x86/encodeopt.asm \
	vp8/encoder/x86/fwalsh_sse2.asm \
	vp8/encoder/x86/quantize_mmx.asm \
	vp8/encoder/x86/ssim_opt_x86_64.asm \
	vp8/encoder/x86/subtract_mmx.asm \
	vp8/encoder/x86/subtract_sse2.asm \
	vp8/encoder/x86/temporal_filter_apply_sse2.asm \
	vp9/common/arm/neon/vp9_avg_neon_asm.asm \
	vp9/common/arm/neon/vp9_convolve8_avg_neon_asm.asm \
	vp9/common/arm/neon/vp9_convolve8_neon_asm.asm \
	vp9/common/arm/neon/vp9_copy_neon_asm.asm \
	vp9/common/arm/neon/vp9_idct16x16_1_add_neon_asm.asm \
	vp9/common/arm/neon/vp9_idct16x16_add_neon_asm.asm \
	vp9/common/arm/neon/vp9_idct32x32_1_add_neon_asm.asm \
	vp9/common/arm/neon/vp9_idct32x32_add_neon_asm.asm \
	vp9/common/arm/neon/vp9_idct4x4_1_add_neon_asm.asm \
	vp9/common/arm/neon/vp9_idct4x4_add_neon_asm.asm \
	vp9/common/arm/neon/vp9_idct8x8_1_add_neon_asm.asm \
	vp9/common/arm/neon/vp9_idct8x8_add_neon_asm.asm \
	vp9/common/arm/neon/vp9_loopfilter_16_neon_asm.asm \
	vp9/common/arm/neon/vp9_loopfilter_4_neon_asm.asm \
	vp9/common/arm/neon/vp9_loopfilter_8_neon_asm.asm \
	vp9/common/arm/neon/vp9_mb_lpf_neon.asm \
	vp9/common/arm/neon/vp9_reconintra_neon_asm.asm \
	vp9/common/arm/neon/vp9_save_reg_neon.asm \
	vp9/common/x86/vp9_copy_sse2.asm \
	vp9/common/x86/vp9_high_intrapred_sse2.asm \
	vp9/common/x86/vp9_high_subpixel_8t_sse2.asm \
	vp9/common/x86/vp9_high_subpixel_bilinear_sse2.asm \
	vp9/common/x86/vp9_idct_ssse3_x86_64.asm \
	vp9/encoder/x86/vp9_sad4d_sse2.asm \
	vp9/encoder/x86/vp9_sad_sse2.asm \
	vp9/encoder/x86/vp9_sad_sse3.asm \
	vp9/encoder/x86/vp9_sad_sse4.asm \
	vp9/encoder/x86/vp9_sad_ssse3.asm \
	vp9/encoder/x86/vp9_ssim_opt_x86_64.asm \
	vp9/encoder/x86/vp9_subpel_variance.asm \
	vp9/encoder/x86/vp9_subtract_sse2.asm \
	vp9/encoder/x86/vp9_temporal_filter_apply_sse2.asm \
	vpx_ports/emms.asm \
	vpx_ports/x86_abi_support.asm \
	$(NULL)