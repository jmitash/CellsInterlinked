function(configure_template_files)
    file(GLOB_RECURSE CI_TEMPLATE_SRCFILES
            RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
            CONFIGURE_DEPENDS
            "template/**/*.in" "../common/template/**/*.in")
    foreach (CI_TEMPLATE_SRCFILE IN ITEMS ${CI_TEMPLATE_SRCFILES})
        # Remove .in
        string(REGEX REPLACE "\\.in$" "" CI_TEMPLATE_DESTFILE ${CI_TEMPLATE_SRCFILE})
        # template/ to generated/
        string(REGEX REPLACE "^template" "generated" CI_TEMPLATE_DESTFILE ${CI_TEMPLATE_DESTFILE})
        # ../common/template to generated/
        string(REGEX REPLACE "^../common/template" "generated" CI_TEMPLATE_DESTFILE ${CI_TEMPLATE_DESTFILE})
        message(VERBOSE "Template file will be configured: ${CI_TEMPLATE_SRCFILE} --- ${CI_TEMPLATE_DESTFILE}")
        configure_file(${CI_TEMPLATE_SRCFILE} ${CI_TEMPLATE_DESTFILE})
    endforeach ()
endfunction()