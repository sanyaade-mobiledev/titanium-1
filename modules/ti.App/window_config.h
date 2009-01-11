/**
 * Appcelerator Titanium - licensed under the Apache Public License 2
 * see LICENSE in the root folder for details on the license. 
 * Copyright (c) 2008 Appcelerator, Inc. All Rights Reserved.
 */
#ifndef TI_WINDOW_CONFIG_H_
#define TI_WINDOW_CONFIG_H_

#include <string>

#include "app_api.h"
#include "app_config.h"

namespace ti {

class TITANIUM_APP_API WindowConfig
{
private:
	std::string winid, url, title;
	int x, y, width, height, minWidth, minHeight, maxWidth, maxHeight;
	float transparency;

	bool visible, maximizable, minimizable, closeable,
		resizable, fullscreen, usingChrome, usingScrollbars;

	void SetDefaults();

public:
	static int DEFAULT_POSITION;

	WindowConfig() { SetDefaults(); }
	WindowConfig(void* data);

	std::string ToString();

	// window accessors
	std::string& GetURL() { return url; }
	void SetURL(std::string& url_) { url = url_; }
	std::string& GetTitle() { return title; }
	void SetTitle(std::string& title_) { title = title_; }
	std::string& GetID() { return winid; }
	void SetID(std::string id_) { winid = id_; }

	int GetX() { return x; }
	void SetX(int x_) { x = x_; }
	int GetY() { return y; }
	void SetY(int y_) { y = y_; }
	int GetWidth() { return width; }
	void SetWidth(int width_) { width = width_; }
	int GetHeight() { return height; }
	void SetHeight(int height_) { height = height_; }
	int GetMinWidth() { return minWidth; }
	void SetMinWidth(int minWidth_) { minWidth = minWidth_; }
	int GetMinHeight() { return minHeight; }
	void SetMinHeight(int minHeight_) { minHeight = minHeight_; }
	int GetMaxWidth() { return maxWidth; }
	void SetMaxWidth(int maxWidth_) { maxWidth = maxWidth_; }
	int GetMaxHeight() { return maxHeight; }
	void SetMaxHeight(int maxHeight_) { maxHeight = maxHeight_; }

	float GetTransparency() { return transparency; }
	void SetTransparency(float transparency_) { transparency = transparency_; }
	bool IsVisible() { return visible; }
	void SetVisible(bool visible_) { visible = visible_; }
	bool IsMaximizable() { return maximizable; }
	void SetMaximizable(bool maximizable_) { maximizable = maximizable_; }
	bool IsMinimizable() { return minimizable; }
	void SetMinimizable(bool minimizable_) { minimizable = minimizable_; }
	bool IsCloseable() { return closeable; }
	void SetCloseable(bool closeable_) { closeable = closeable_; }
	bool IsResizable() { return resizable; }
	void SetResizable(bool resizable_) { resizable = resizable_; }
	bool IsFullscreen() { return fullscreen; }
	void SetFullscreen(bool fullscreen_) { fullscreen = fullscreen_; }
	bool IsUsingChrome() { return usingChrome; }
	void SetUsingChrome(bool usingChrome_) { usingChrome = usingChrome_; }
	bool IsUsingScrollbars() { return usingScrollbars; }
	void SetUsingScrollbars(bool usingScrollbars_) { usingScrollbars = usingScrollbars_; }
};

}
#endif