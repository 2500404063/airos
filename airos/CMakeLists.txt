cmake_minimum_required(VERSION 3.25.0)

add_library(airos STATIC    airos_queue.c
                            airos_task.c
                            airos_task.s)
target_compile_options(airos PUBLIC ${COMPILE_FLAG_CPU}
                                    ${COMPILE_FLAG_FPU}
                                    ${COMPILE_FLAG_ABI}
                                    ${COMPILE_FLAG_CODE})