#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <cmath>
#include <filesystem> // C++17 以上版本
#include <SDL.h>
#include <SDL_image.h>

#include "ProgressBar.hpp"

namespace fs = std::filesystem;

// 函式用於將影像放大，並遞迴處理子目錄
void enlargeImages(const std::string& folderPath, double scaleFactor, const std::string& outputPath) {
	// 檢查資料夾路徑是否有效
	if (!fs::exists(folderPath) || !fs::is_directory(folderPath)) {
		std::cerr << "錯誤：提供的路徑不是有效的輸入資料夾路徑：" << outputPath << std::endl;
		return;
	}

	// 檢查輸出路徑是否有效
	if (!fs::exists(outputPath) || !fs::is_directory(outputPath)) {
		fs::create_directory(outputPath);
	}


	// 迭代資料夾中的所有檔案和子目錄
	for (const auto& entry : fs::directory_iterator(folderPath)) {
		if (entry.is_directory()) {
			// 遞迴呼叫自身來處理子目錄
			std::string newOutputPath = (fs::path(outputPath) / entry.path().filename()).string();
			if (!fs::exists(newOutputPath)) {
				fs::create_directory(newOutputPath);
			}
			enlargeImages(entry.path().string(), scaleFactor, newOutputPath);
		}
		else if (entry.is_regular_file() && entry.path().extension() == ".png") {
			// 處理 .png 檔案
			std::string imagePath = entry.path().string();
			// 使用 SDL_image 讀取影像
			SDL_Surface* imageSurface = IMG_Load(imagePath.c_str());
			if (!imageSurface) {
				//std::cerr << "無法讀取影像：" << imagePath << "，原因: " << IMG_GetError() << std::endl;
				continue; // 讀取失敗，跳過此影像
			}

			// 計算新的尺寸
			int newWidth = static_cast<int>(imageSurface->w * scaleFactor);
			int newHeight = static_cast<int>(imageSurface->h * scaleFactor);

			// 建立新的 SDL_Surface 來儲存放大的影像
			SDL_Surface* enlargedSurface = SDL_CreateRGBSurface(0, newWidth, newHeight, 32,
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
				0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF
#else
				0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000
#endif
			);
			if (!enlargedSurface) {
				//std::cerr << "無法建立放大的影像表面： " << SDL_GetError() << std::endl;
				SDL_FreeSurface(imageSurface);
				continue;
			}

			// 使用 SDL_SoftStretch 進行縮放
			if (SDL_SoftStretch(imageSurface, NULL, enlargedSurface, NULL) < 0) {
				//std::cerr << "影像縮放失敗： " << SDL_GetError() << std::endl;
				SDL_FreeSurface(imageSurface);
				SDL_FreeSurface(enlargedSurface);
				continue;
			}

			// 建立輸出檔案名稱，放在對應的子資料夾
			std::string outputImagePath = (fs::path(outputPath) / ( entry.path().filename().string())).string();

			// 使用 SDL_image 將放大的影像寫入新的檔案
			if (IMG_SavePNG(enlargedSurface, outputImagePath.c_str()) < 0) {
				//std::cerr << "無法寫入放大的影像：" << outputImagePath << "，原因: " << std::endl;
			}
			else {
				//std::cout << "成功放大並儲存影像：" << outputImagePath << std::endl;
			}

			// 釋放 SDL_Surface
			SDL_FreeSurface(imageSurface);
			SDL_FreeSurface(enlargedSurface);
		}
		
		
	}
}