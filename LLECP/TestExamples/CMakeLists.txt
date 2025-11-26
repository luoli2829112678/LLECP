foreach(EXAMPLE 
		RT_ScriptExamples 
		MotionPlanningExamples
    EtherCATMasterExamples
    STExecEngineExamples
    )
    add_executable(${EXAMPLE} ${EXAMPLE}.cpp)
    target_link_libraries(${EXAMPLE} PUBLIC 
    RT_Script     
    CIA402Axis
    EtherCATMaster
    SoftMotion
    motion_algorithm
    STExecEngine
    )
endforeach()
