#pragma once

#include "MinMaxClamp.hpp"
#include "Enums.hpp"

class Color {
public:
	Color() = default;

	Color(colorModel model, Uint16 c1, Uint8 c2, Uint8 c3, Uint8 alpha = 255)
		: alpha(alpha) {
		switch (model) {
		case colorModel::RGB:
			r = static_cast<Uint8>(c1);
			g = c2;
			b = c3;
			toHSV();
			break;
		case colorModel::HSV:
			h = c1;
			s = c2;
			v = c3;
			toRGB();
			break;
		}
	}

	Uint8 r = 0;
	Uint8 g = 0;
	Uint8 b = 0;
	Uint16 h = 0;
	Uint8 s = 0;
	Uint8 v = 0;

	Uint8 alpha = 255;

private:
	void toHSV() {
		double rIn = static_cast<double>(r) / 255;
		double gIn = static_cast<double>(g) / 255;
		double bIn = static_cast<double>(b) / 255;
		double hOut, sOut, vOut;
		double minimum = mmc::min(rIn, gIn, bIn);
		double maximum = mmc::max(rIn, gIn, bIn);
		double delta = maximum - minimum;

		vOut = maximum;
		if (delta < 0.00001) {
			sOut = 0;
			hOut = 0;
		}
		if (maximum > 0.0) {
			sOut = delta / maximum;
		} else {
			sOut = 0;
			hOut = 0;
		}
		if (rIn >= maximum)
			hOut = (gIn - bIn) / delta;
		else if (gIn >= maximum)
			hOut = 2.0 + (bIn - rIn) / delta;
		else
			hOut = 4.0 + (rIn - gIn) / delta;

		hOut *= 60.0;

		if (hOut < 0.0)
			hOut += 360.0;

		h = static_cast<Uint16>(hOut);
		s = static_cast<Uint8>(sOut * 100);
		v = static_cast<Uint8>(vOut * 100);
	}

	void toRGB() {
		double hIn = static_cast<double>(h);
		double sIn = static_cast<double>(s) / 100;
		double vIn = static_cast<double>(v) / 100;
		double rOut, gOut, bOut;
		double hh, p, q, t, ff;

		if (sIn == 0.0) {
			rOut = vIn;
			gOut = vIn;
			bOut = vIn;
		} else {
			hh = hIn;
			if (hh >= 360.0)
				hh = 0.0;

			hh /= 60.0;
			auto i = static_cast<long>(hh);
			ff = hh - i;
			p = vIn * (1.0 - sIn);
			q = vIn * (1.0 - (sIn * ff));
			t = vIn * (1.0 - (sIn * (1.0 - ff)));

			switch (i) {
			case 0:
				rOut = vIn;
				gOut = t;
				bOut = p;
				break;
			case 1:
				rOut = q;
				gOut = vIn;
				bOut = p;
				break;
			case 2:
				rOut = p;
				gOut = vIn;
				bOut = t;
				break;

			case 3:
				rOut = p;
				gOut = q;
				bOut = vIn;
				break;
			case 4:
				rOut = t;
				gOut = p;
				bOut = vIn;
				break;
			case 5:
			default:
				rOut = vIn;
				gOut = p;
				bOut = q;
				break;
			}
		}

		r = static_cast<Uint8>(rOut * 255);
		g = static_cast<Uint8>(gOut * 255);
		b = static_cast<Uint8>(bOut * 255);
	}
};
