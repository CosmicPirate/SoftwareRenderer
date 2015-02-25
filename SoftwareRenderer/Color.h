#ifndef _COLOR_H_
#define _COLOR_H_



class RgbColor
{
public:
	RgbColor() {}
	RgbColor(int r, int g, int b) : RgbColor(r, g, b, 255)
	{
	}
	RgbColor(int r, int g, int b, int a)
	{
		_channels[0] = r;
		_channels[1] = g;
		_channels[2] = b;
		_channels[3] = a;
	}
	//RgbColor(unsigned char * color, int spectrum)
	//{
	//	if (channels < 3) throw "not enugh channels";
	//	if (channels == 3)
	//	{
	//		_channels[0] = color[0];
	//		_channels[1] = color[1];
	//		_channels[2] = color[2];
	//	}
	//	if (channels > 3)
	//		_channels[3] = color[3];
	//}
	RgbColor operator+(RgbColor c)
	{
		return *this;
	}
	inline int& operator [](const unsigned i)
	{
		if (i >= 3) throw "index out of range";
		return _channels[i];
	}
	inline const int operator [](const unsigned i) const
	{
		if (i >= 3) throw "index out of range";
		return _channels[i];
	}


private:
	int _spectrum = 4;
	int _channels[4];
};

#endif // _COLOR_H_