#pragma once
#ifndef FILEPATH_HPP
#define FILEPATH_HPP
namespace MyAPP {
	struct ResourcesFilePath {
	
		static constexpr auto BGMPath = MY_RESOURCE_DIR "/BGM/Ring08.wav";
		/// <summary>
		/// 生成式人工智慧導論製作的手寫字型
		/// </summary>
		static constexpr auto MyFontPath = MY_RESOURCE_DIR "/Font/t112590005.ttf";
		static constexpr auto ArialFontPath = MY_RESOURCE_DIR "/Font/arial.ttf";
		static constexpr auto BackgroundImagePath = MY_RESOURCE_DIR "/Image/Background/cat.jpg";
		static constexpr auto marioImagePath = "imgs/super mario/Mario/frame0.png";

		/// <summary>
		/// 1-1地圖圖片路徑
		/// </summary>
		static constexpr auto Background_1_1_ImagePath = R"(imgs\super mario\Maps\SuperMarioBrosMap1-1main-up.png)";

		/// <summary>
		/// 1-1水管地圖圖片路徑
		/// </summary>
		static constexpr auto Background_1_1_Pipe_ImagePath = "imgs/super mario/Maps/SuperMarioBrosMap1-1inpipe.png";

		/// <summary>
		/// 1-1到1-2過場圖片路徑
		/// </summary>
		static constexpr auto Background_1_1_to_1_2_ImagePath = "imgs/super mario/Maps/SuperMarioBrosMap1-1 to 1-2.png";

		///// <summary>
		/// 1-2地圖圖片路徑
		/// </summary>
		static constexpr auto Background_1_2_ImagePath = "imgs/super mario/Maps/SuperMarioBrosMap1-2main_new.png";

		/// <summary>
		/// 1-2水管地圖圖片路徑
		/// </summary>
		static constexpr auto Background_1_2_Pipe_ImagePath = "imgs/super mario/Maps/SuperMarioBrosMap1-2BG in pipe.png";

		/// <summary>
		/// 磚頭圖片路徑
		/// </summary>
		static constexpr auto BlockImagePath = /*"imgs/super mario/floor.png";*/ "imgs/super mario/1-1/BrickBlockBrown.png";

		/// <summary>
		/// 磚頭圖片路徑(深色)
		/// </summary>
		static constexpr auto BlockDarkImagePath = "imgs/super mario/BrickBlockDark.png";

		/// <summary>
		/// 地板圖片路徑
		/// </summary>
		static constexpr auto FloorImagePath = "imgs/super mario/floor.png";

		/// <summary>
		/// 地板圖片路徑(深色)
		/// </summary>
		static constexpr auto FloorDarkImagePath = "imgs/super mario/floordark.png";

		/// <summary>
		/// 階梯圖片路徑
		/// </summary>
		static constexpr auto StairsBrickImagePath = "imgs/super mario/StairsBrick.png";

		/// <summary>
		/// 階梯圖片路徑(深色)
		/// </summary>
		static constexpr auto StairsBrickDarkImagePath = "imgs/super mario/StairsBrickDark.png";

		static constexpr inline auto EmptyBlockImagePath{ "imgs/super mario/EmptyBlock.png" };
		static constexpr inline auto EmptyBlockDarkImagePath{ "imgs/super mario/EmptyBlockDark.png" };

		// static constexpr auto QuestionBlockPath = "imgs/super mario/QuestionBlock/frame0.png";
		// static constexpr auto EmptyBlockImagePath = "imgs/super mario/EmptyBlock.png";
		// static constexpr auto BlueblockImagePath = /*"imgs/super mario/StairsBrick.png";*/ "imgs/super mario/Blueblock.png";
		static constexpr auto Ground_Theme = MY_RESOURCE_DIR "/BGM/01. Ground Theme.mp3";
		static constexpr auto Lost_a_Life = MY_RESOURCE_DIR "/BGM/08. Lost a Life.mp3";
		static constexpr auto Underground_Theme = MY_RESOURCE_DIR "/BGM/02. Underground Theme.mp3";
		static constexpr auto Game_Over = MY_RESOURCE_DIR "/BGM/09. Game Over.mp3";
		// static constexpr auto Underground_Theme_fix = MY_RESOURCE_DIR "/BGM/02 (mp3cut.net).mp3";

		// static constexpr auto CheckPointPath = "imgs/super mario/CheckPoint.png";
	};

}

#endif // !FILEPATH_HPP
