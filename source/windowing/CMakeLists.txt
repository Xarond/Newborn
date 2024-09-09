INCLUDE_DIRECTORIES (
    ${NEWBORN_EXTERN_INCLUDES}
    ${NEWBORN_CORE_INCLUDES}
    ${NEWBORN_BASE_INCLUDES}
    ${NEWBORN_GAME_INCLUDES}
    ${NEWBORN_PLATFORM_INCLUDES}
    ${NEWBORN_APPLICATION_INCLUDES}
    ${NEWBORN_RENDERING_INCLUDES}
    ${NEWBORN_WINDOWING_INCLUDES}
  )

SET (newborn_windowing_HEADERS
        NewbornButtonGroup.hpp
        NewbornButtonWidget.hpp
        NewbornCanvasWidget.hpp
        NewbornFlowLayout.hpp
        NewbornFuelWidget.hpp
        NewbornGuiContext.hpp
        NewbornGuiReader.hpp
        NewbornGuiTypes.hpp
        NewbornImageWidget.hpp
        NewbornImageStretchWidget.hpp
        NewbornItemGridWidget.hpp
        NewbornItemSlotWidget.hpp
        NewbornKeyBindings.hpp
        NewbornLabelWidget.hpp
        NewbornLargeCharPlateWidget.hpp
        NewbornLayout.hpp
        NewbornListWidget.hpp
        NewbornPane.hpp
        NewbornPaneManager.hpp
        NewbornPortraitWidget.hpp
        NewbornProgressWidget.hpp
        NewbornScrollArea.hpp
        NewbornSliderBar.hpp
        NewbornStackWidget.hpp
        NewbornTabSet.hpp
        NewbornTextBoxWidget.hpp
        NewbornVerticalLayout.hpp
        NewbornWidget.hpp
        NewbornWidgetLuaBindings.hpp
        NewbornWidgetParsing.hpp
    )

SET (newborn_windowing_SOURCES
        NewbornButtonGroup.cpp
        NewbornButtonWidget.cpp
        NewbornCanvasWidget.cpp
        NewbornFlowLayout.cpp
        NewbornFuelWidget.cpp
        NewbornGuiContext.cpp
        NewbornGuiReader.cpp
        NewbornGuiTypes.cpp
        NewbornImageWidget.cpp
        NewbornImageStretchWidget.cpp
        NewbornItemGridWidget.cpp
        NewbornItemSlotWidget.cpp
        NewbornKeyBindings.cpp
        NewbornLayout.cpp
        NewbornLabelWidget.cpp
        NewbornLargeCharPlateWidget.cpp
        NewbornListWidget.cpp
        NewbornPane.cpp
        NewbornPaneManager.cpp
        NewbornPortraitWidget.cpp
        NewbornProgressWidget.cpp
        NewbornScrollArea.cpp
        NewbornSliderBar.cpp
        NewbornStackWidget.cpp
        NewbornTabSet.cpp
        NewbornTextBoxWidget.cpp
        NewbornVerticalLayout.cpp
        NewbornWidget.cpp
        NewbornWidgetLuaBindings.cpp
        NewbornWidgetParsing.cpp
    )

ADD_LIBRARY (newborn_windowing OBJECT ${newborn_windowing_SOURCES} ${newborn_windowing_HEADERS})
