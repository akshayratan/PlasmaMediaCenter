set(metadatapicturebackend_SRCS
    metadatapicturemodel.cpp
    ../abstractmetadatabackend.cpp
    metadatapicturebackend.cpp
)

qt4_automoc(${metadatapicturebackend_SRCS})

kde4_add_plugin(pmc_metadatapicturebackend ${metadatapicturebackend_SRCS})

target_link_libraries(pmc_metadatapicturebackend
    plasmamediacenter
    ${KDE4_KDECORE_LIBS}
    ${QT_QTCORE_LIBRARIES}
)

install(TARGETS pmc_metadatapicturebackend DESTINATION ${PLUGIN_INSTALL_DIR})
install(FILES metadatapicturebackend.desktop DESTINATION ${SERVICES_INSTALL_DIR})
