#ifndef __COMMONMACRO_H__
#define __COMMONMACRO_H__

#define ROWS_SIZE 8
#define COlUMNS_SIZE 8


enum StarType
{
	kEmpty,
	kColorStar,
	kBounceBall,
	kDeadVine,
	kLiveVine,
	kStump,
	kBomb,
	kIron,
	kDiamond,
	kKey,
	kStone,

	kStarTypeCount,
};


enum Colors
{
	kColorRandom,

	kColorRed,
	kColorYellow,
	kColorBlue,
	kColorGreen,
	kColorPurple,
};


#define NOTIFY_VIEWS(_FUNC_ ,...)						\
for (size_t index = 0; index < m_views.size(); ++index) \
{														\
	m_views[index]->_FUNC_(__VA_ARGS__);				\
	}
#endif 
