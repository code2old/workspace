# utils.cmake

#���¶��嵱ǰĿ���Դ�ļ���__FILE__��
function(redefine_file_macro targetname)
    #��ȡ��ǰĿ�������Դ�ļ�
    get_target_property(source_files "${targetname}" SOURCES)
    #����Դ�ļ�
    foreach(sourcefile ${source_files})
        #��ȡ��ǰԴ�ļ��ı������
        get_property(defs SOURCE "${sourcefile}"
            PROPERTY COMPILE_DEFINITIONS)
        #��ȡ��ǰ�ļ��ľ���·��
        get_filename_component(filepath "${sourcefile}" ABSOLUTE)
        #������·���е���Ŀ·���滻�ɿ�,�õ�Դ�ļ��������Ŀ·�������·��
        string(REPLACE ${PROJECT_SOURCE_DIR}/ "" relpath ${filepath})
        #������Ҫ�ӵı������(__FILE__����)��ӵ�ԭ���ı����������
        list(APPEND defs "__FILE__=\"${relpath}\"")
        #��������Դ�ļ��ı������
        set_property(
            SOURCE "${sourcefile}"
            PROPERTY COMPILE_DEFINITIONS ${defs}
            )
    endforeach()
endfunction()
