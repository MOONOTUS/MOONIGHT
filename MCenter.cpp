#include"MCenter.h"

QImage blurred(const QImage& image, const QRect& rect, qint32 radius, bool alphaOnly)
{
	qint32 tab[] = { 14, 10, 8, 6, 5, 5, 4, 3, 3, 3, 3, 2, 2, 2, 2, 2, 2 };
	qint32 alpha = (radius < 1) ? 16 : (radius > 17) ? 1 : tab[radius - 1];

	QImage result = image.convertToFormat(QImage::Format_ARGB32_Premultiplied);
	qint32 r1 = rect.top();
	qint32 r2 = rect.bottom();
	qint32 c1 = rect.left();
	qint32 c2 = rect.right();

	qint32 bpl = result.bytesPerLine();
	qint32 rgba[4];
	unsigned char* p;

	qint32 i1 = 0;
	qint32 i2 = 3;

	if (alphaOnly)
		i1 = i2 = (QSysInfo::ByteOrder == QSysInfo::BigEndian ? 0 : 3);

	for (qint32 col = c1; col <= c2; col++) {
		p = result.scanLine(r1) + col * 4;
		for (qint32 i = i1; i <= i2; i++)
			rgba[i] = p[i] << 4;

		p += bpl;
		for (qint32 j = r1; j < r2; j++, p += bpl)
			for (qint32 i = i1; i <= i2; i++)
				p[i] = (rgba[i] += ((p[i] << 4) - rgba[i]) * alpha / 16) >> 4;
	}

	for (qint32 row = r1; row <= r2; row++) {
		p = result.scanLine(row) + c1 * 4;
		for (qint32 i = i1; i <= i2; i++)
			rgba[i] = p[i] << 4;

		p += 4;
		for (qint32 j = c1; j < c2; j++, p += 4)
			for (qint32 i = i1; i <= i2; i++)
				p[i] = (rgba[i] += ((p[i] << 4) - rgba[i]) * alpha / 16) >> 4;
	}

	for (qint32 col = c1; col <= c2; col++) {
		p = result.scanLine(r2) + col * 4;
		for (qint32 i = i1; i <= i2; i++)
			rgba[i] = p[i] << 4;

		p -= bpl;
		for (qint32 j = r1; j < r2; j++, p -= bpl)
			for (qint32 i = i1; i <= i2; i++)
				p[i] = (rgba[i] += ((p[i] << 4) - rgba[i]) * alpha / 16) >> 4;
	}

	for (qint32 row = r1; row <= r2; row++) {
		p = result.scanLine(row) + c2 * 4;
		for (qint32 i = i1; i <= i2; i++)
			rgba[i] = p[i] << 4;

		p -= 4;
		for (qint32 j = c1; j < c2; j++, p -= 4)
			for (qint32 i = i1; i <= i2; i++)
				p[i] = (rgba[i] += ((p[i] << 4) - rgba[i]) * alpha / 16) >> 4;
	}

	return image;
}

void GaussiamBlur(qint32 r, qreal variance, QImage& img)//参数说明：模糊半径r，方差variance，QImage图像
{
    if (variance < 0)
    {
        throw "variance must be greater than 0";
    }
    if (r == 0)
    {
        return;
    }

    //lambda函数说明：x：模糊半径，o：方差，返回：1维高斯函数的运算结果
    auto Gaussian1D = [](qreal x, qreal variance_)->qreal {return (qExp(-(qPow(x, 2) / (2 * qPow(variance_, 2))))) / (variance_ * 2 * M_PI); };

    qint32 imgw = img.width();
    qint32 imgh = img.height();

    qint32 kernelSize = 2 * r + 1;
    qint32 twor = 2 * r;
    QVector<qreal> weight(kernelSize);
    qreal weightsum = 0.0;

    //生成高斯核
    for (qint32 i = 0; i <= twor; i++)
    {
        weight[i] = Gaussian1D(i - r, variance);
        weightsum += weight[i];
    }
    //权重和归一化
    for (auto& i : weight)
    {
        i /= weightsum;
    }

    //这部分使用快速高斯模糊算法：用一维高斯函数处理两次，降低时间复杂度
    //边缘处理忽略，但在一个方向上至少会处理一次
    //使用滑动窗口算法

    //横向
    for (qint32 y = 0; y < imgh; y++)
    {
        QVector<qreal> tempred(imgw);
        QVector<qreal> tempgreen(imgw);
        QVector<qreal> tempblue(imgw);
        qreal redsum = 0;
        qreal greensum = 0;
        qreal bluesum = 0;

        for (qint32 x = 0; x < imgw; x++)
        {
            QColor color(img.pixel(x, y));
            qint32 q = x % kernelSize;
            tempred[x] = color.red() * weight[q];
            tempgreen[x] = color.green() * weight[q];
            tempblue[x] = color.blue() * weight[q];

            redsum += tempred[x];
            greensum += tempgreen[x];
            bluesum += tempblue[x];

            if (x >= twor)
            {
                img.setPixel(x - r, y, qRgb(redsum, greensum, bluesum));
                redsum -= tempred[x - twor];
                greensum -= tempgreen[x - twor];
                bluesum -= tempblue[x - twor];
            }
        }
    }

    //纵向
    for (qint32 x = 0; x < imgw; x++)
    {
        QVector<qreal> tempred(imgw);
        QVector<qreal> tempgreen(imgw);
        QVector<qreal> tempblue(imgw);
        qreal redsum = 0;
        qreal greensum = 0;
        qreal bluesum = 0;

        for (qint32 y = 0; y < imgh; y++)
        {
            QColor color(img.pixel(x, y));
            qint32 q = y % kernelSize;
            tempred[y] = color.red() * weight[q];
            tempgreen[y] = color.green() * weight[q];
            tempblue[y] = color.blue() * weight[q];

            redsum += tempred[y];
            greensum += tempgreen[y];
            bluesum += tempblue[y];

            if (y >= twor)
            {
                img.setPixel(x, y - r, qRgb(redsum, greensum, bluesum));
                redsum -= tempred[y - twor];
                greensum -= tempgreen[y - twor];
                bluesum -= tempblue[y - twor];
            }
        }
    }
}