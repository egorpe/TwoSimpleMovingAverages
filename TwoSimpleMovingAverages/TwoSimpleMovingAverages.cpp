//---------------------------------------------------------------------------
// Sample indicator with two SMAs from chapter 14 of Black Algo Trading
// course.
//---------------------------------------------------------------------------

#include <windows.h>
#include "IndicatorInterfaceUnit.h"
#include "TechnicalFunctions.h"


// External variables
int FastMovingAveragePeriod;
int SlowMovingAveragePeriod;

// Buffers
TIndexBuffer FastMovingAverageBuffer;
TIndexBuffer SlowMovingAverageBuffer;

//---------------------------------------------------------------------------
// Initialize indicator
//---------------------------------------------------------------------------
EXPORT void __stdcall Init() {
  // define properties
  IndicatorShortName("Two Simple Moving Averages");
  SetOutputWindow(ow_ChartWindow);

  // register options
  AddSeparator("Common");

  RegOption("Fast Moving Average Period", ot_Integer, &FastMovingAveragePeriod);
  SetOptionRange("Fast Moving Average Period", 1, MaxInt);
  FastMovingAveragePeriod = 5;

  RegOption("Slow Moving Average Period", ot_Integer, &SlowMovingAveragePeriod);
  SetOptionRange("Slow Moving Average Period", 1, MaxInt);
  SlowMovingAveragePeriod = 25;

  // create buffers
  FastMovingAverageBuffer = CreateIndexBuffer();
  SlowMovingAverageBuffer = CreateIndexBuffer();
  
  IndicatorBuffers(2);
  SetIndexBuffer(0, FastMovingAverageBuffer);
  SetIndexBuffer(1, SlowMovingAverageBuffer);
  
  SetIndexStyle(0, ds_Line, psSolid, 1, clRed);
  SetIndexLabel(0, "Fast Moving Average");
  SetIndexStyle(1, ds_Line, psSolid, 1, clBlue);
  SetIndexLabel(1, "Slow Moving Average");

}

EXPORT void __stdcall OnParamsChange() {}

/// @brief Calculates the moving average for the i-th bar using a period.
double calculateSimpleMovingAverage(int i, int period) {
	double total = 0;

	for (int currentBar = i; currentBar < i + period; currentBar++) {
		total += Close(currentBar);
	}

	return total / period;
}

/// @brief Calculate the value for indicator buffers for the i-th bar.
void calculate(int i) {
	FastMovingAverageBuffer[i] =
		calculateSimpleMovingAverage(i, FastMovingAveragePeriod);
	SlowMovingAverageBuffer[i] =
		calculateSimpleMovingAverage(i, SlowMovingAveragePeriod);
}

//---------------------------------------------------------------------------
// Calculate requested bar
//---------------------------------------------------------------------------
EXPORT void __stdcall Calculate(int index) {
	calculate(index);
}


