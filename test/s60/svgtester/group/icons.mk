# ============================================================================
#  Name	 : Icons_scalable_dc.mk
#  Part of  : svgtester
#
#  Description: This is file for creating .mif file (scalable icon)
# 
# ============================================================================


ifeq (WINS,$(findstring WINS, $(PLATFORM)))
ZDIR=$(EPOCROOT)epoc32\release\$(PLATFORM)\$(CFG)\Z
else
ZDIR=$(EPOCROOT)epoc32\data\z
endif

TARGETDIR=$(ZDIR)\resource\apps

ICONS_IN=$(TARGETDIR)\svgtester_in.mif
ICONS_EXP=$(TARGETDIR)\svgtester_exp.mif
ICONS_OUT=$(TARGETDIR)\svgtester_out.mif

HEADERDIR=$(EPOCROOT)epoc32\include
HEADER_IN=$(HEADERDIR)\svgtester_in.mbg
HEADER_EXP=$(HEADERDIR)\svgtester_exp.mbg
HEADER_OUT=$(HEADERDIR)\svgtester_out.mbg

ICONDIR=..\gfx

IN=..\..\..\testdata\input
OUT=..\..\..\testdata\output
EXP=..\..\..\testdata\expected

#IN=..\..\..\testdata\output
#OUT=..\..\..\testdata\output
#EXP=..\..\..\testdata\output


do_nothing :
	@rem do_nothing

MAKMAKE : do_nothing

BLD : do_nothing

CLEAN :
	del /q /f $(ICONS_IN) $(ICONS_EXP) $(ICONS_OUT) $(HEADER_IN) $(HEADER_OUT) $(HEADER_EXP)

LIB : do_nothing

CLEANLIB : do_nothing

# ----------------------------------------------------------------------------
# NOTE: if you have JUSTINTIME enabled for your S60 3rd FP1 or newer SDK
# and this command crashes, consider adding "/X" to the command line.
# See <http://forum.nokia.com/document/Forum_Nokia_Technical_Library_v1_35/contents/FNTL/Build_process_fails_at_mif_file_creation_in_S60_3rd_Ed_FP1_SDK.htm>
# ----------------------------------------------------------------------------

#RESOURCE : $(ICONS_IN) $(ICONS_EXP) $(ICONS_OUT) 
RESOURCE : $(ICONS_OUT) 

$(ICONS_IN) :
	mifconv $(ICONS_IN) /H$(HEADER_IN) \
		$(IN)\complex\Sea_mine.svg\
		$(IN)\complex\eye.svg \
		$(IN)\complex\kompozer.svg \
		$(IN)\complex\butterfly_invalid.svg \
		$(IN)\complex\tiger.svg \
		$(IN)\complex\example1.svg \
		$(IN)\complex\butterfly.svg \
		$(IN)\complex\circles.svg \
		$(IN)\complex\example2.svg \
		$(IN)\complex\lion.svg \
		$(IN)\gradients\linear.svg \
		$(IN)\gradients\radial.svg \
		$(IN)\gradients\radial2.svg \
		$(IN)\misc\handler.svg \
		$(IN)\misc\animate_color.svg \
		$(IN)\misc\font_src.svg \
		$(IN)\misc\prefetch.svg \
		$(IN)\misc\audio.svg \
		$(IN)\misc\external_image.svg\
		$(IN)\misc\animate_transform.svg \
		$(IN)\misc\text_area.svg \
		$(IN)\misc\a2.svg \
		$(IN)\misc\animate_text_on_path.svg \
		$(IN)\misc\tbreak.svg \
		$(IN)\misc\metadata.svg \
		$(IN)\misc\animate_sequental.svg \
		$(IN)\misc\solid_color.svg \
		$(IN)\misc\defs.svg \
		$(IN)\misc\animation.svg\
		$(IN)\misc\animate.svg \
		$(IN)\misc\inkscape_namespace.svg\
		$(IN)\misc\text.svg\
		$(IN)\misc\a.svg \
		$(IN)\misc\foreign_object.svg \
		$(IN)\misc\video.svg \
		$(IN)\misc\discard.svg \
		$(IN)\misc\embedded_image.svg \
		$(IN)\misc\glyph.svg \
		$(IN)\misc\opacity.svg \
		$(IN)\misc\font.svg \
		$(IN)\misc\use.svg \
		$(IN)\misc\glyph_complex.svg\
		$(IN)\shapes\path.svg \
		$(IN)\shapes\overlapping_ellipses.svg \
		$(IN)\shapes\line.svg\
		$(IN)\shapes\rectangle.svg\
		$(IN)\shapes\path_curved.svg\
		$(IN)\shapes\polyline.svg\
		$(IN)\shapes\circle.svg \
		$(IN)\shapes\ellipse.svg \
		$(IN)\shapes\polygon_triangle.svg \
		$(IN)\filters\specular_lighting.svg \
		$(IN)\filters\gaussian_blur.svg \
		$(IN)\filters\morphology.svg \
		$(IN)\filters\blend_filter.svg \
		$(IN)\filters\multifilter.svg \
		$(IN)\filters\color_matrix.svg \
		$(IN)\filters\component_transfer.svg \
		$(IN)\filters\offset.svg\
		$(IN)\complex\Anonymous_two_red_dice.svg

#$(IN)\complex\Anonymous_two_red_dice.svg



## Files that crash the sdk converter:
#		$(IN)\misc\animate_motion.svg  
#		$(IN)\shapes\rectangle_with_opacity.svg
#		$(IN)\shapes\rectangle_with_opacity2.svg \

## Files that crash cause converter to fail (not crash):
#		$(OUT)\shapes\rectangle_with_rounded_corners.svg 
# NOTE this one, only fails for non converted file.
#		$(IN)\misc\script.svg 

$(ICONS_EXP) :
	mifconv $(ICONS_EXP) /H$(HEADER_EXP) \
		$(EXP)\complex\Sea_mine.svg \
		$(EXP)\complex\eye.svg \
		$(EXP)\complex\kompozer.svg \
		$(EXP)\complex\butterfly_invalid.svg \
		$(EXP)\complex\tiger.svg \
		$(EXP)\complex\example1.svg \
		$(EXP)\complex\butterfly.svg \
		$(EXP)\complex\circles.svg \
		$(EXP)\complex\example2.svg \
		$(EXP)\complex\lion.svg \
		$(EXP)\gradients\linear.svg \
		$(EXP)\gradients\radial.svg \
		$(EXP)\gradients\radial2.svg \
		$(EXP)\misc\handler.svg \
		$(EXP)\misc\animate_color.svg \
		$(EXP)\misc\font_src.svg \
		$(EXP)\misc\prefetch.svg \
		$(EXP)\misc\audio.svg \
		$(EXP)\misc\external_image.svg \
		$(EXP)\misc\animate_transform.svg \
		$(EXP)\misc\text_area.svg \
		$(EXP)\misc\a2.svg \
		$(EXP)\misc\animate_text_on_path.svg \
		$(EXP)\misc\tbreak.svg \
		$(EXP)\misc\metadata.svg \
		$(EXP)\misc\animate_sequental.svg \
		$(EXP)\misc\solid_color.svg \
		$(EXP)\misc\defs.svg \
		$(EXP)\misc\animation.svg \
		$(EXP)\misc\animate.svg \
		$(EXP)\misc\inkscape_namespace.svg\
		$(EXP)\misc\text.svg\
		$(EXP)\misc\a.svg \
		$(EXP)\misc\foreign_object.svg \
		$(EXP)\misc\video.svg  \
		$(EXP)\misc\discard.svg \
		$(EXP)\misc\embedded_image.svg \
		$(EXP)\misc\glyph.svg \
		$(EXP)\misc\opacity.svg \
		$(EXP)\misc\font.svg \
		$(EXP)\misc\use.svg \
		$(EXP)\misc\glyph_complex.svg \
		$(EXP)\misc\script.svg \
		$(EXP)\shapes\path.svg \
		$(EXP)\shapes\overlapping_ellipses.svg \
		$(EXP)\shapes\line.svg\
		$(EXP)\shapes\rectangle.svg\
		$(EXP)\shapes\path_curved.svg\
		$(EXP)\shapes\polyline.svg \
		$(EXP)\shapes\circle.svg \
		$(EXP)\shapes\ellipse.svg \
		$(EXP)\shapes\polygon_triangle.svg \
		$(EXP)\filters\specular_lighting.svg \
		$(EXP)\filters\gaussian_blur.svg \
		$(EXP)\filters\morphology.svg \
		$(EXP)\filters\blend_filter.svg \
		$(EXP)\filters\multifilter.svg \
		$(EXP)\filters\color_matrix.svg \
		$(EXP)\filters\component_transfer.svg \
		$(EXP)\filters\offset.svg

#	$(EXP)\complex\Anonymous_two_red_dice.svg

## Files that crash the sdk converter:
#		$(EXP)\misc\animate_motion.svg  
#		$(EXP)\shapes\rectangle_with_opacity.svg
#		$(EXP)\shapes\rectangle_with_opacity2.svg \

## Files that crash cause converter to fail (not crash):
#		$(OUT)\shapes\rectangle_with_rounded_corners.svg 


########################
########################
########################
########################
########################

# Below icons cause mifconv to crash on S3 SDK:


$(ICONS_OUT) :
	echo "********************* ICON CONVERSION BEGIN **********************"
	mifconv $(ICONS_OUT) -H$(HEADER_OUT) \
		-c24,8 $(OUT)\complex\qtinfo.svg \
		-c24,8 $(OUT)\complex\QTinfo_2.svg \
		-c24,8 $(OUT)\complex\dartboard.svg \
		-c24,8 $(OUT)\complex\distortion.svg \
		-c24,8 $(OUT)\complex\LetterA.svg \
		-c24,8 $(OUT)\complex\M.svg \
		-c24,8 $(OUT)\complex\RasorLogin.svg \
		-c24,8 $(OUT)\complex\salami.svg \
		-c24,8 $(OUT)\complex\sushi.svg \
		-c24,8 $(OUT)\complex\TornPaper02.svg \
		-c24,8 $(OUT)\complex\1305613953.svg \
		-c24,8 $(OUT)\complex\1305615579.svg \
		-c24,8 $(OUT)\complex\Andy_Tools.svg \
		-c24,8 $(OUT)\complex\Apple2.svg \
		-c24,8 $(OUT)\complex\Brain.svg \
		-c24,8 $(OUT)\complex\Chrisdesign_tomato.svg \
		-c24,8 $(OUT)\complex\ColouringBook.svg \
		-c24,8 $(OUT)\complex\Constantine.svg \
		-c24,8 $(OUT)\complex\Fedora_splatter.svg \
		-c24,8 $(OUT)\complex\GM_NewTux.svg \
		-c24,8 $(OUT)\complex\Gentoo_logo.svg \
		-c24,8 $(OUT)\complex\Giza_pyramid_complex.svg \
		-c24,8 $(OUT)\complex\Glass.svg \
		-c24,8 $(OUT)\complex\Globe.svg \
		-c24,8 $(OUT)\complex\Nokia6102.svg \
		-c24,8 $(OUT)\complex\Phone2.svg \
		-c24,8 $(OUT)\complex\Posing.svg \
		-c24,8 $(OUT)\complex\Posing3.svg \
		-c24,8 $(OUT)\complex\RedLamborghini.svg \
		-c24,8 $(OUT)\complex\Sea_mine.svg \
		-c24,8 $(OUT)\complex\Snowglobe.svg \
		-c24,8 $(OUT)\complex\Soccer_ball.svg \
		-c24,8 $(OUT)\complex\TheStructorr_cherries.svg \
		-c24,8 $(OUT)\complex\Warning.svg \
		-c24,8 $(OUT)\complex\butterfly.svg \
		-c24,8 $(OUT)\complex\butterfly_invalid.svg \
		-c24,8 $(OUT)\complex\chili.svg \
		-c24,8 $(OUT)\complex\circles.svg \
		-c24,8 $(OUT)\complex\cocktail.svg \
		-c24,8 $(OUT)\complex\countries.svg \
		-c24,8 $(OUT)\complex\example1.svg \
		-c24,8 $(OUT)\complex\example2.svg \
		-c24,8 $(OUT)\complex\exampleTrans.svg \
		-c24,8 $(OUT)\complex\exampleTransNest.svg \
		-c24,8 $(OUT)\complex\eye.svg \
		-c24,8 $(OUT)\complex\eyeball.svg \
		-c24,8 $(OUT)\complex\flomar_DSLR_Camera.svg \
		-c24,8 $(OUT)\complex\freephile_balloons.svg \
		-c24,8 $(OUT)\complex\kompozer.svg \
		-c24,8 $(OUT)\complex\lion.svg \
		-c24,8 $(OUT)\complex\sailor.svg \
		-c24,8 $(OUT)\complex\scarlet_svg.svg \
		-c24,8 $(OUT)\complex\silhouette.svg \
		-c24,8 $(OUT)\complex\tiger.svg \
		-c24,8 $(OUT)\complex\tommek_Women.svg \
		-c24,8 $(OUT)\complex\tonyk_lips.svg \
		-c24,8 $(OUT)\complex\two_red_dice.svg \
		-c24,8 $(OUT)\complex\virginfest.svg \
		-c24,8 $(OUT)\complex\webmichl_zippo.svg \
		-c24,8 $(OUT)\filters\blend_filter.svg \
		-c24,8 $(OUT)\filters\color_matrix.svg \
		-c24,8 $(OUT)\filters\component_transfer.svg \
		-c24,8 $(OUT)\filters\gaussian_blur.svg \
		-c24,8 $(OUT)\filters\morphology.svg \
		-c24,8 $(OUT)\filters\multifilter.svg \
		-c24,8 $(OUT)\filters\offset.svg \
		-c24,8 $(OUT)\filters\specular_lighting.svg \
		-c24,8 $(OUT)\gradients\linear.svg \
		-c24,8 $(OUT)\gradients\radial.svg \
		-c24,8 $(OUT)\gradients\radial2.svg \
		-c24,8 $(OUT)\misc\a.svg \
		-c24,8 $(OUT)\misc\a2.svg \
		-c24,8 $(OUT)\misc\animate.svg \
		-c24,8 $(OUT)\misc\animate_color.svg \
		-c24,8 $(OUT)\misc\animate_sequental.svg \
		-c24,8 $(OUT)\misc\animate_text_on_path.svg \
		-c24,8 $(OUT)\misc\animate_transform.svg \
		-c24,8 $(OUT)\misc\animation.svg \
		-c24,8 $(OUT)\misc\audio.svg \
		-c24,8 $(OUT)\misc\defs.svg \
		-c24,8 $(OUT)\misc\discard.svg \
		-c24,8 $(OUT)\misc\embedded_image.svg \
		-c24,8 $(OUT)\misc\external_image.svg \
		-c24,8 $(OUT)\misc\font.svg \
		-c24,8 $(OUT)\misc\font_src.svg \
		-c24,8 $(OUT)\misc\foreign_object.svg \
		-c24,8 $(OUT)\misc\glyph.svg \
		-c24,8 $(OUT)\misc\glyph_complex.svg \
		-c24,8 $(OUT)\misc\handler.svg \
		-c24,8 $(OUT)\misc\inkscape_namespace.svg \
		-c24,8 $(OUT)\misc\metadata.svg \
		-c24,8 $(OUT)\misc\opacity.svg \
		-c24,8 $(OUT)\misc\prefetch.svg \
		-c24,8 $(OUT)\misc\script.svg \
		-c24,8 $(OUT)\misc\solid_color.svg \
		-c24,8 $(OUT)\misc\tbreak.svg \
		-c24,8 $(OUT)\misc\text.svg \
		-c24,8 $(OUT)\misc\text_area.svg \
		-c24,8 $(OUT)\misc\use.svg \
		-c24,8 $(OUT)\misc\video.svg \
		-c24,8 $(OUT)\shapes\circle.svg \
		-c24,8 $(OUT)\shapes\ellipse.svg \
		-c24,8 $(OUT)\shapes\elliptical_arcs.svg \
		-c24,8 $(OUT)\shapes\line.svg \
		-c24,8 $(OUT)\shapes\overlapping_ellipses.svg \
		-c24,8 $(OUT)\shapes\path.svg \
		-c24,8 $(OUT)\shapes\path_curved.svg \
		-c24,8 $(OUT)\shapes\polygon_triangle.svg \
		-c24,8 $(OUT)\shapes\polyline.svg \
		-c24,8 $(OUT)\shapes\rect_opacity.svg \
		-c24,8 $(OUT)\shapes\rect_opacity2.svg \
		-c24,8 $(OUT)\shapes\rect_rounded.svg \
		-c24,8 $(OUT)\shapes\rectangle.svg
		
FREEZE : do_nothing

SAVESPACE : do_nothing

RELEASABLES :
	@echo $(ICONS_IN) $(ICONS_EXP) $(ICONS_OUT)

FINAL : do_nothing

