#ifndef CITY_SCAPE_HPP
#define CITY_SCAPE_HPP

#include "city_annotation.hpp"
#include "city_block.hpp"
#include "city_view.hpp"

//-----------------------------------------------------------------------------

namespace qt_book {

using namespace ivl;
using ::rand;

//-----------------------------------------------------------------------------

class city_scape : public main_window
{
	graphics_scene *scene;
	city_view *view;

public:

//-----------------------------------------------------------------------------

	city_scape()
	{
		scene = new graphics_scene(-22.25, -22.25, 1980, 1980);
		scene->setBackgroundBrush(QColor(255, 255, 238));
		generate_blocks();

		view = new city_view;
		view->setScene(scene);
		setCentralWidget(view);

		setWindowTitle(tr("Cityscape"));
	}

private:

//-----------------------------------------------------------------------------

	void generate_blocks()
	{
		QSet <QString> names;
		names << "Adams" << "Agnew" << "Arthur" << "Breckinridge"
				<< "Buchanan" << "Burr" << "Bush" << "Calhoun" << "Carter"
				<< "Cheney" << "Cleveland" << "Clinton" << "Colfax"
				<< "Coolidge" << "Curtis" << "Dallas" << "Dawes"
				<< "Eisenhower" << "Fairbanks" << "Fillmore" << "Ford"
				<< "Garfield" << "Garner" << "Gerry" << "Gore" << "Grant"
				<< "Hamlin" << "Harding" << "Harrison" << "Hayes"
				<< "Hendricks" << "Hobart" << "Hoover" << "Humphrey"
				<< "Jackson" << "Jefferson" << "Johnson" << "Kennedy"
				<< "King" << "Lincoln" << "Madison" << "Marshall"
				<< "McKinley" << "Mondale" << "Monroe" << "Morton"
				<< "Nixon" << "Pierce" << "Polk" << "Quayle" << "Reagan"
				<< "Rockefeller" << "Roosevelt" << "Sherman" << "Stevenson"
				<< "Taft" << "Taylor" << "Tompkins" << "Truman" << "Tyler"
				<< "Van Buren" << "Wallace" << "Washington" << "Wheeler"
				<< "Wilson";

		QSetIterator <QString> i(names);
		for (int y = 0; y < 44; ++y)
		{
			for (int x = 0; x < 44; ++x)
			{
				int percentile;
				if (x > 20 && x < 24 && y > 20 && y < 24)
					percentile = rand() % (rand() % 2 != 0 ? 10 : 100);
				else if (x > 18 && x < 26 && y > 18 && y < 26)
					percentile = rand() % (rand() % 3 != 0 ? 10 : 100);
				else if (x > 15 && x < 29 && y > 15 && y < 29)
					percentile = rand() % (rand() % 5 != 0 ? 10 : 100);
				else
					percentile = rand() % 100;

				city_block::Kind kind;
				QString name;

				if (percentile == 0)
				{
					kind = city_block::Park;
					name = tr("%1 Park");
				}
				else if (percentile <= 2)
					kind = city_block::SmallBuilding;
				else if (percentile <= 4)
				{
					kind = city_block::Hospital;
					name = tr("%1 Hospital");
				}
				else if (percentile == 5)
				{
					kind = city_block::Hall;
					name = tr("%1 Hall");
				}
				else if (percentile <= 7)
				{
					kind = city_block::Building;
					name = tr("%1 Bldg");
				}
				else if (percentile <= 9)
				{
					kind = city_block::Tower;
					name = tr("%1 Tower");
				}
				else if (percentile <= 15)
					kind = city_block::LShapedBlock;
				else if (percentile <= 30)
					kind = city_block::LShapedBlockPlusSmallBlock;
				else if (percentile <= 70)
					kind = city_block::TwoBlocks;
				else
					kind = city_block::BlockPlusTwoSmallBlocks;

				city_block *block = new city_block(kind);
				block->setPos(QPointF(x * 44.5, y * 44.5));
				scene->addItem(block);

				if (!name.isEmpty())
				{
					if (!i.hasNext())
						i.toFront();

					bool major = (rand() % 10 == 0);
					annotation* ann = new annotation(name.arg(i.next()), major);
					ann->setPos(block->pos());
					scene->addItem(ann);
				}
			}
		}
	}

};

//-----------------------------------------------------------------------------

}  // namespace qt_book

//-----------------------------------------------------------------------------

#endif  // CITY_SCAPE_HPP
