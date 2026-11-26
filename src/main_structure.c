#include "layouts.h"

#include <clay.h>

#define max_size                                                               \
	(Clay_Sizing) { CLAY_SIZING_GROW(), CLAY_SIZING_GROW() }
#define COLOR_WHITE {255, 255, 255, 255}

Clay_RenderCommandArray draw_main_window() {
	Clay_BeginLayout();
	// draw here and only here
	CLAY({
		.id = CLAY_ID("window"),
		.backgroundColor = {43, 41, 51, 255},
		.layout =
			{
				.layoutDirection = CLAY_TOP_TO_BOTTOM,
				.sizing = max_size,
				.padding = {16, 16, 16, 16},
				.childGap = 16,
			},
	}) {
		CLAY({
			.id = CLAY_ID("top_bar"),
			.backgroundColor = {200, 200, 200, 255},
			.cornerRadius = CLAY_CORNER_RADIUS(25),
			.layout = {.sizing = {CLAY_SIZING_GROW(), CLAY_SIZING_FIXED(100)}},
		}) {
			// top options here
		}
		CLAY({
			.id = CLAY_ID("main_body"),
			.backgroundColor = {200, 200, 200, 255},
			.cornerRadius = CLAY_CORNER_RADIUS(25),
			.layout = {.sizing = max_size, .padding = {16, 16, 16, 16}},
		}) {
			CLAY({
				.id = CLAY_ID("view"),
				.backgroundColor = COLOR_WHITE,
				.layout = {.sizing = max_size},
			}) {
				// draw the logic gates here
			}
		}
	}
	return Clay_EndLayout();
}
