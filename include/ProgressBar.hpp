#ifndef ProgressBar_HPP
#define ProgressBar_HPP
#include <iostream>

inline void showProgressBar(int total, int current, int width = 50) noexcept {
	// �p�⧹���ʤ���
	float ratio = (float)current / total;
	int completedWidth = (int)(ratio * width);

	// ��X�i�ױ�
	std::cout << "[";
	for (int i = 0; i < width; ++i) {
		if (i < completedWidth) {
			std::cout << "="; // �w��������
		}
		else {
			std::cout << " "; // ����������
		}
	}
	std::cout << "] " << (int)(ratio * 100) << "%";
	std::cout << "\r"; // �^��歺�A�л\���e����X
	std::cout.flush(); // �j���s��X�w�İ�
}
#endif // !ProgressBar_HPP
