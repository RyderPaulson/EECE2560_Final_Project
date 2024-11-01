project(Forecaster_lib)

set(HEADER_FILES
        Algorithm.h
        Market.h
        io.h
)

set(SOURCE_FILES
        Algorithm.cpp
        Market.cpp
        io.cpp
)

add_library(Forecaster_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})