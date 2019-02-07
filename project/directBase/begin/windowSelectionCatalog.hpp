#include "windowSelectionCatalog.h"

#include "windowMvCatalog.h"

template<typename T>
inline void windowSelectionCatalog<T>::initBind(void)
{
	windowMvCatalog<T>* bind = (windowMvCatalog<T>*)_bindWindow;

	_bindIndex = &bind->getIndex();
	_bindOffset = &bind->getOffset();
}
