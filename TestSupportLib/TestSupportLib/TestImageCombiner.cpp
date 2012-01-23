#include "stdafx.h"
#include "BaseLib/FastFunctions.h"
#include "BaseLib/FileUtil.h"
#include "BaseLib/NaiveFile.h"
#include "CoreLib/TypeConverter.h"
#include "StandardLib/Unknowns.h"
#include "SupportLib/ImageReader.h"
#include "SupportLib/ImageWriter.h"
#include "SupportLib/ImageCelsSource.h"
#include "SupportLib/ImageRGBToGrey.h"
#include "SupportLib/ImageCelSourceBorders.h"
#include "SupportLib/ImageSourceDiskFile.h"
#include "SupportLib/ImageCombiner.h"
#include "TestLib/Assert.h"
#include "TestImageCombiner.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestImageCombinerMask(void)
{

	CImageCelSourceBorders	cBorder;
	CImageCombiner			cCombiner;
	CImage					cImage;
	CImageCelsSource		cSource;
	SImageColour			sColour;

	sColour.c[0] = 0;
	sColour.c[1] = 0;
	sColour.c[2] = 0;
	sColour.c[3] = 0;

	cBorder.Init(&sColour);

	cSource.Init();
	cSource.AddDiskFileSource("Input\\cel4.png", "Cel 4", &cBorder);
	cSource.AddDiskFileSource("Input\\cel6.png", "Cel 6", &cBorder);

	cSource.Load();

	cCombiner.Init(&cImage, ICL_Best, ICS_Arbitrary, ICC_FromCels);
	cCombiner.AddCels(cSource.GetCels());
	cCombiner.Combine();

	WriteImage(&cImage, "Output\\CombineMask.png");
	WriteImage(&cImage, "Output\\CombineMask.raw");
	AssertFileMemory("input\\CombineMask.raw", cImage.mcChannels.GetData(), cImage.GetByteSize());

	cImage.Kill();
	cCombiner.Kill();
	cSource.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestImageCombiner(void)
{
	BeginTests();

	TestImageCombinerMask();

	TestStatistics();
}

