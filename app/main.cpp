#include <iostream>


#include "KVStore.h"

#include "CommandParser.h"

#include "CommandFactory.h"



int main()
{

    KVStore store(100);


    CommandParser parser;



    std::string input;


    while(std::getline(std::cin,input))
    {


        auto parsed =
            parser.parse(input);



        auto command =
            CommandFactory::create(parsed);



        if(command)
        {

            std::cout
                << command->execute(store)
                << std::endl;

        }

        else
        {

            std::cout
                << "Unknown command"
                << std::endl;

        }


    }


    return 0;

}