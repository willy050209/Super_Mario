#pragma once
#ifndef FILEPATH_HPP
#define FILEPATH_HPP
#include "MyDefine.hpp"

#include <array>
#include <string>
#include <algorithm>
#include <execution>

namespace MyAPP {
	/// <summary>
	/// �ɮ׸��|
	/// </summary>
	struct MyResourcesFilePath {
		CANNOTCREATE(MyResourcesFilePath);
		struct MAP {
			CANNOTCREATE(MAP);

			/// <summary>
			/// 1-1�a�ϹϤ����|
			/// </summary>
			static constexpr auto Background_1_1_ImagePath = R"(imgs\super mario\Maps\SuperMarioBrosMap1-1main-up.png)";

			/// <summary>
			/// 1-1���ަa�ϹϤ����|
			/// </summary>
			static constexpr auto Background_1_1_Pipe_ImagePath = "imgs/super mario/Maps/SuperMarioBrosMap1-1inpipe.png";

			/// <summary>
			/// 1-1��1-2�L���Ϥ����|
			/// </summary>
			static constexpr auto Background_1_1_to_1_2_ImagePath = "imgs/super mario/Maps/SuperMarioBrosMap1-1 to 1-2.png";

			///// <summary>
			/// 1-2�a�ϹϤ����|
			/// </summary>
			static constexpr auto Background_1_2_ImagePath = "imgs/super mario/Maps/SuperMarioBrosMap1-2main_new.png";

			/// <summary>
			/// 1-2���ަa�ϹϤ����|
			/// </summary>
			static constexpr auto Background_1_2_Pipe_ImagePath = "imgs/super mario/Maps/SuperMarioBrosMap1-2BG in pipe.png";

			static constexpr auto Background_1_2_to_1_4_ImagePath = "imgs/super mario/Maps/SuperMarioBrosMap1-2BGupground.png";

			static constexpr auto Background_1_4_ImagePath = "imgs/super mario/Maps/SuperMarioBrosMap1-4BG.png";

			static constexpr auto Background_Died_ImagePath = "imgs/super mario/Maps/supermario_pass_stage-FIX.png";
			
			static constexpr auto Form_1_1_Images = MY_RESOURCE_DIR "/MAP/Form_1_1_Images.txt";
			static constexpr auto Form_1_1_Characters = MY_RESOURCE_DIR "/MAP/Form_1_1_Characters.txt";
			static constexpr auto Form_1_1_Pipe_Images = MY_RESOURCE_DIR "/MAP/Form_1_1_Pipe_Images.txt";
			static constexpr auto Form_1_1_Pipe_Characters = MY_RESOURCE_DIR "/MAP/Form_1_1_Pipe_Characters.txt";
			static constexpr auto Form_1_1_to_1_2_Images = MY_RESOURCE_DIR "/MAP/Form_1_1_to_1_2_Images.txt";
			static constexpr auto Form_1_2_Images = MY_RESOURCE_DIR "/MAP/Form_1_2_Images.txt";
			static constexpr auto Form_1_2_Characters = MY_RESOURCE_DIR "/MAP/Form_1_2_Characters.txt";
			static constexpr auto Form_1_2_Pipe_Images = MY_RESOURCE_DIR "/MAP/Form_1_2_Pipe_Images.txt";
			static constexpr auto Form_1_2_Pipe_Characters = MY_RESOURCE_DIR "/MAP/Form_1_2_Pipe_Characters.txt";
			static constexpr auto Form_1_2_to_1_4_Images = MY_RESOURCE_DIR "/MAP/Form_1_2_to_1_4_Images.txt";
			static constexpr auto Form_1_4_Images = MY_RESOURCE_DIR "/MAP/Form_1_4_Images.txt";
			static constexpr auto Form_1_4_Characters = MY_RESOURCE_DIR "/MAP/Form_1_4_Characters.txt";
		};
		
		class Kapoo {
		public:
			CANNOTCREATE(Kapoo);

			static inline auto getCapoo_giphyFrame() noexcept {
				static auto Capoo_giphyFrame = initCapoo_giphyFrame();
				return Capoo_giphyFrame;
			}
		private:
			static inline std::array<std::string, 57> initCapoo_giphyFrame() noexcept {
				std::array<std::string, 57> Capoo_giphyFrame;
				int index = 0;
				std::for_each(std::execution::seq, Capoo_giphyFrame.begin(), Capoo_giphyFrame.end(), [&](auto& it) {
					(it) = std::string(MY_RESOURCE_DIR "/Kapoo/Capoo_giphy/frame") + std::to_string(index++) + std::string(".png");
				});
				return Capoo_giphyFrame;
			}
		};

		static constexpr auto BGMPath = MY_RESOURCE_DIR "/BGM/Ring08.wav";
		/// <summary>
		/// �ͦ����H�u���z�ɽ׻s�@����g�r��
		/// </summary>
		static constexpr auto MyFontPath = MY_RESOURCE_DIR "/Font/t112590005.ttf";
		static constexpr auto ArialFontPath = MY_RESOURCE_DIR "/Font/arial.ttf";
		static constexpr auto BackgroundImagePath = MY_RESOURCE_DIR "/Image/Background/cat.jpg";
		static constexpr auto marioImagePath = "imgs/super mario/Mario/frame0.png";
		static constexpr auto TimesNewRoman = MY_RESOURCE_DIR "/Font/times.ttf";
		static constexpr auto SuperMarioFont = MY_RESOURCE_DIR "/Font/Super Mario Bros. NES.ttf";

		/// <summary>
		/// �j�Y�Ϥ����|
		/// </summary>
		static constexpr auto BlockImagePath = "imgs/super mario/1-1/BrickBlockBrown.png";

		/// <summary>
		/// �j�Y�Ϥ����|(�`��)
		/// </summary>
		static constexpr auto BlockDarkImagePath = "imgs/super mario/BrickBlockDark.png";

		static constexpr auto BlockGreyImagePath = "imgs/super mario/BrickBlockCastle.png";

		/// <summary>
		/// �a�O�Ϥ����|
		/// </summary>
		static constexpr auto FloorImagePath = "imgs/super mario/floor.png";

		/// <summary>
		/// �a�O�Ϥ����|(�`��)
		/// </summary>
		static constexpr auto FloorDarkImagePath = "imgs/super mario/floordark.png";

		static constexpr auto FloorGreyImagePath = "imgs/super mario/floorCastle.png";

		/// <summary>
		/// ����Ϥ����|
		/// </summary>
		static constexpr auto StairsBrickImagePath = "imgs/super mario/StairsBrick.png";

		static constexpr auto MovingPlatform = R"(imgs\super mario\MovingPlatform.png)";

		/// <summary>
		/// ����Ϥ����|(�`��)
		/// </summary>
		static constexpr auto StairsBrickDarkImagePath = "imgs/super mario/StairsBrickDark.png";

		static constexpr inline auto EmptyBlockImagePath{ "imgs/super mario/EmptyBlock.png" };
		static constexpr inline auto EmptyBlockDarkImagePath{ "imgs/super mario/EmptyBlockDark.png" };
		static constexpr inline auto EmptyBlockGreyImagePath{ "imgs/super mario/EmptyBlockGrey.png" };

		static constexpr inline auto FrieBall{ R"(imgs\super mario\FireBall.png)" };

		static constexpr inline auto Koopa_Fire{ R"(imgs\super mario\cmp.png)" };

		static constexpr inline auto BlabkBrick{ R"(imgs\super mario\blackBrick.png)" };

		static constexpr inline auto BridgeBrick{ R"(imgs\super mario\Bridge.png)" };

		static constexpr inline auto MarioStanding{ R"(imgs\super mario\MarioStanding.png)" };

		// static constexpr auto QuestionBlockPath = "imgs/super mario/QuestionBlock/frame0.png";
		// static constexpr auto EmptyBlockImagePath = "imgs/super mario/EmptyBlock.png";
		// static constexpr auto BlueblockImagePath = /*"imgs/super mario/StairsBrick.png";*/ "imgs/super mario/Blueblock.png";

		static constexpr auto endImagePath = "imgs/super mario/end.png";

		static constexpr auto PipeImagePath = "imgs/super mario/pipe.png";

		static constexpr auto PipeDarkImagePath = "imgs/super mario/pipeDark.png";

		static constexpr auto Ground_Theme = MY_RESOURCE_DIR "/BGM/01. Ground Theme.mp3";
		static constexpr auto Lost_a_Life = MY_RESOURCE_DIR "/BGM/08. Lost a Life.mp3";
		static constexpr auto Underground_Theme = MY_RESOURCE_DIR "/BGM/02. Underground Theme.mp3";
		static constexpr auto Game_Over = MY_RESOURCE_DIR "/BGM/09. Game Over.mp3";
		// static constexpr auto Underground_Theme_fix = MY_RESOURCE_DIR "/BGM/02 (mp3cut.net).mp3";

		// static constexpr auto CheckPointPath = "imgs/super mario/CheckPoint.png";
	};

}

#endif // !FILEPATH_HPP
