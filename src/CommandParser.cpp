#include "CommandParser.h"


#include <sstream>



ParsedCommand CommandParser::parse(
    const std::string& input
)
{

    std::stringstream ss(input);


    std::string token;


    std::vector<std::string> tokens;



    while(ss >> token)
    {
        tokens.push_back(token);
    }



    ParsedCommand cmd;



    if(tokens.empty())
    {
        cmd.type=CommandType::UNKNOWN;

        return cmd;
    }



    if(tokens[0]=="SET")
    {
        cmd.type=CommandType::SET;
    }
    else if(tokens[0]=="GET")
    {
        cmd.type=CommandType::GET;
    }
    else if(tokens[0]=="DEL")
    {
        cmd.type=CommandType::DEL;
    }
    else
    {
        cmd.type=CommandType::UNKNOWN;
    }



    for(size_t i=1;i<tokens.size();i++)
    {
        cmd.args.push_back(tokens[i]);
    }



    return cmd;

}