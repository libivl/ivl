#ifndef CITY_VIEW_HPP
#define CITY_VIEW_HPP

#include <cmath>

//-----------------------------------------------------------------------------

namespace qt_book {

using namespace ivl;

//-----------------------------------------------------------------------------

struct city_view : public graphics_view
{

	city_view(QWidget *parent = 0) : graphics_view(parent)
	{
		setDragMode(ScrollHandDrag);
	}

protected:

//-----------------------------------------------------------------------------

	void wheelEvent(QWheelEvent *event)
	{
		double degrees = event->delta() / 8.0;
		double steps = degrees / 15.0;
		double factor = std::pow(1.125, steps);
		scale(factor, factor);
	}

};

//-----------------------------------------------------------------------------

}  // namespace qt_book

//-----------------------------------------------------------------------------

#endif  // CITY_VIEW_HPP
