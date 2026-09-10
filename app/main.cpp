#include "ThreadPool.h"

#include <iostream>


int main()
{

    ThreadPool pool(4);


    for(int i=0;i<10;i++)
    {

        pool.submit(

            [i]()
            {

                std::cout
                    <<"task "
                    <<i
                    <<std::endl;

            }

        );

    }


    return 0;

}