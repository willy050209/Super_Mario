#ifndef ProgressBar_HPP
inline void showProgressBar(int total, int current, int width = 50) noexcept {
	// 計算完成百分比
	float ratio = (float)current / total;
	int completedWidth = (int)(ratio * width);

	// 輸出進度條
	std::cout << "[";
	for (int i = 0; i < width; ++i) {
		if (i < completedWidth) {
			std::cout << "="; // 已完成部分
		}
		else {
			std::cout << " "; // 未完成部分
		}
	}
	std::cout << "] " << (int)(ratio * 100) << "%";
	std::cout << "\r"; // 回到行首，覆蓋之前的輸出
	std::cout.flush(); // 強制刷新輸出緩衝區
}
#endif // !ProgressBar_HPP
