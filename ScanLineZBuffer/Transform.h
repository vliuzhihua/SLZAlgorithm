#pragma once


class Transform{
public:
	//默认是先位移再缩放的。
	double x, y, z;
	double scale;//缩放程度，默认为1，表示不缩放。

	//其他的变换我暂时不做处理。
};