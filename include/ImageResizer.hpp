#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <cmath>
#include <filesystem> // C++17 �H�W����
#include <SDL.h>
#include <SDL_image.h>

#include "ProgressBar.hpp"

namespace fs = std::filesystem;

int total = 0, current = 0;

inline int get_all_files(const fs::path& directory) {
	int result{0};
	for (const auto& entry : fs::recursive_directory_iterator(directory)) {
		if (fs::is_regular_file(entry) && entry.path().extension() == ".png") {
			result++;
		}
	}
	return result;
}

// �禡�Ω�N�v����j�A�û��j�B�z�l�ؿ�
void enlargeImages(const std::string& folderPath, double scaleFactor, const std::string& outputPath) {
	// �ˬd��Ƨ����|�O�_����
	if (!fs::exists(folderPath) || !fs::is_directory(folderPath)) {
		std::cerr << "���~�G���Ѫ����|���O���Ī���J��Ƨ����|�G" << outputPath << std::endl;
		return;
	}

	// �ˬd��X���|�O�_����
	if (!fs::exists(outputPath) || !fs::is_directory(outputPath)) {
		fs::create_directory(outputPath);
	}


	// ���N��Ƨ������Ҧ��ɮשM�l�ؿ�
	for (const auto& entry : fs::directory_iterator(folderPath)) {
		if (entry.is_directory()) {
			// ���j�I�s�ۨ��ӳB�z�l�ؿ�
			std::string newOutputPath = (fs::path(outputPath) / entry.path().filename()).string();
			if (!fs::exists(newOutputPath)) {
				fs::create_directory(newOutputPath);
			}
			enlargeImages(entry.path().string(), scaleFactor, newOutputPath);
		}
		else if (entry.is_regular_file() && entry.path().extension() == ".png") {
			// �B�z .png �ɮ�
			std::string imagePath = entry.path().string();
			// �ϥ� SDL_image Ū���v��
			SDL_Surface* imageSurface = IMG_Load(imagePath.c_str());
			if (!imageSurface) {
				//std::cerr << "�L�kŪ���v���G" << imagePath << "�A��]: " << IMG_GetError() << std::endl;
				continue; // Ū�����ѡA���L���v��
			}

			// �p��s���ؤo
			int newWidth = static_cast<int>(imageSurface->w * scaleFactor);
			int newHeight = static_cast<int>(imageSurface->h * scaleFactor);

			// �إ߷s�� SDL_Surface ���x�s��j���v��
			SDL_Surface* enlargedSurface = SDL_CreateRGBSurface(0, newWidth, newHeight, 32,
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
				0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF
#else
				0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000
#endif
			);
			if (!enlargedSurface) {
				//std::cerr << "�L�k�إߩ�j���v�����G " << SDL_GetError() << std::endl;
				SDL_FreeSurface(imageSurface);
				continue;
			}

			// �ϥ� SDL_SoftStretch �i���Y��
			if (SDL_SoftStretch(imageSurface, NULL, enlargedSurface, NULL) < 0) {
				//std::cerr << "�v���Y�񥢱ѡG " << SDL_GetError() << std::endl;
				SDL_FreeSurface(imageSurface);
				SDL_FreeSurface(enlargedSurface);
				continue;
			}

			// �إ߿�X�ɮצW�١A��b�������l��Ƨ�
			std::string outputImagePath = (fs::path(outputPath) / ( entry.path().filename().string())).string();

			// �ϥ� SDL_image �N��j���v���g�J�s���ɮ�
			if (IMG_SavePNG(enlargedSurface, outputImagePath.c_str()) < 0) {
				//std::cerr << "�L�k�g�J��j���v���G" << outputImagePath << "�A��]: " << std::endl;
			}
			else {
				//std::cout << "���\��j���x�s�v���G" << outputImagePath << std::endl;
			}
			showProgressBar(total, current++);
			// ���� SDL_Surface
			SDL_FreeSurface(imageSurface);
			SDL_FreeSurface(enlargedSurface);
		}
		
		
	}
}