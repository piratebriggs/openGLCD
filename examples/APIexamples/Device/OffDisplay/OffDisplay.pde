/*
 * OffDisplay - openGLCD API example
 *
 * Example of using:
 * OnDisplay()
 * OffDisplay()
 *
 * status = OnDisplay();
 * status = OffDisplay();
 *
 * OnDisplay() turns on the display pixels
 * OffDisplay() turns off the display pixels
 *
 * Created by Bill Perry 2013-08-01
 * bperrybap@opensource.billsworld.billandterrie.com
 */

#include <openGLCD.h>
#include <fonts/SystemFont5x7.h>

void setup()
{

	GLCD.Init();
	GLCD.SelectFont(SystemFont5x7);
	GLCD.DrawString("OffDisplay test", gTextfmt_center, gTextfmt_center);

}

void loop(void)
{
	int status = GLCD.OnDisplay(); // turn on pixels
	if(status != GLCD_ENOERR)
	{
		// failed, code here handles error, if needed
	}

	delay(2000);

	status = GLCD.OffDisplay(); // turn off pixels
	if(status != GLCD_ENOERR)
	{
		// failed, code here handles error, if needed
	}
	delay(1000);
}
