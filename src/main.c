#include "layouts.h"
#define RAYGUI_IMPLEMENTATION
#define CLAY_IMPLEMENTATION
#include <clay.h>
#include <clay/renderers/raylib/clay_renderer_raylib.c>
#include <raylib.h>
#include <renderers/raylib/raylib.h>
#include <stdint.h>

const int FONT_ID_BODY_16 = 0;
#define max_size                                                               \
	(Clay_Sizing) { CLAY_SIZING_GROW(), CLAY_SIZING_GROW() }
#define COLOR_WHITE {255, 255, 255, 255}

void RenderHeaderButton(Clay_String text) {
	CLAY({
		.layout = {.padding = {16, 16, 8, 8}},
		.backgroundColor = {140, 140, 140, 255},
		.cornerRadius = {5, 5, 5, 5},
	}) {
		CLAY_TEXT(text, CLAY_TEXT_CONFIG({.fontId = FONT_ID_BODY_16,
										  .fontSize = 16,
										  .textColor = {255, 255, 255, 255}}));
	}
}

int main() {
	Clay_Raylib_Initialize(0, 0, "Clay - Raylib Renderer Example",
						   FLAG_MSAA_4X_HINT | FLAG_FULLSCREEN_MODE |
							   FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
	// clay's memory stuff
	uint64_t clayRequiredMemory = Clay_MinMemorySize();
	Clay_Arena clayMemory = {.memory = malloc(clayRequiredMemory),
							 .capacity = clayRequiredMemory};
	Clay_Initialize(clayMemory,
					(Clay_Dimensions){.width = GetScreenWidth(),
									  .height = GetScreenHeight()},
					(Clay_ErrorHandler){0});

	// setting up fonts
	Font fonts[1];
	fonts[FONT_ID_BODY_16] =
		LoadFontEx("resources/Roboto-Regular.ttf", 32, 0, 400);
	SetTextureFilter(fonts[FONT_ID_BODY_16].texture, TEXTURE_FILTER_BILINEAR);
	Clay_SetMeasureTextFunction(Raylib_MeasureText, fonts);

	// seting up blur to give basic AA
	const float renderScale = 1.5;
	RenderTexture2D frame_buffer = LoadRenderTexture(
		GetScreenWidth() * renderScale, GetScreenHeight() * renderScale);
	SetTextureFilter(frame_buffer.texture, TEXTURE_FILTER_BILINEAR);
	Camera2D camera = {.zoom = renderScale};

	while (!WindowShouldClose()) {
		// Run once per frame
		Clay_SetLayoutDimensions((Clay_Dimensions){
			.width = GetScreenWidth(), .height = GetScreenHeight()});
		const Vector2 mouse_pos = GetMousePosition();
		const Vector2 scrolldt = GetMouseWheelMoveV();
		Clay_SetPointerState((Clay_Vector2){mouse_pos.x, mouse_pos.y},
							 IsMouseButtonDown(0));
		Clay_UpdateScrollContainers(
			1, (Clay_Vector2){scrolldt.x * 2.f, scrolldt.y * 2.f},
			GetFrameTime());

		// draw the main window
		Clay_RenderCommandArray render_command = draw_main_window();

		BeginTextureMode(frame_buffer);
		BeginMode2D(camera);
		// execute clay commands
		ClearBackground(BLACK);
		Clay_Raylib_Render(render_command, fonts);
		EndMode2D();
		EndTextureMode();

		// drawing
		BeginDrawing();
		// Setup the back buffer for drawing (clear color and depth buffers)
		// ClearBackground(BLACK);

		DrawTexturePro(frame_buffer.texture,
					   (Rectangle){0, 0, frame_buffer.texture.width,
								   -frame_buffer.texture.height},
					   (Rectangle){0, 0, GetScreenWidth(), GetScreenHeight()},
					   (Vector2){0, 0}, 0.0f, WHITE);
		// end the frame and get ready for the next one  (display frame, poll
		// input, etc...)
		EndDrawing();
	}

	// cleanup
	// unload our texture so it can be cleaned up
	UnloadRenderTexture(frame_buffer);

	// destroy the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}
