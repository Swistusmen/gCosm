#include <gtest/gtest.h>
#include "../../src/Parser/parser.cpp"


TEST(PARSER,EMPTY_COMMAND)
{
    char* argv[1];
    *argv[0]='a';
    int argc=1;
    Parser parser;
    auto a=parser.createProgramDriver(argc,argv);
    ASSERT_EQ(a.doStream,true);
    ASSERT_EQ(a.message,"");
}

TEST(PARSER,RUN_WITH_ANOTHER_PORT)
{
    char* argv[3];
    *argv[0]='a';
    *argv[1]='-lp';
    *argv[2]='8080';
    int argc=3;
    Parser parser;
    auto a=parser.createProgramDriver(argc,argv);
    ASSERT_EQ(a.doStream,true);
    ASSERT_EQ(a.message,"");
    ASSERT_EQ(a.ListeningPort,8080);
}

TEST(PARSER,RUN_WITH_ANOTHER_SAVE)
{
    char* argv[3];
    *argv[0]='a';
    *argv[1]='-s';
    *argv[2]='8080';
    int argc=3;
    Parser parser;
    auto a=parser.createProgramDriver(argc,argv);
    ASSERT_EQ(a.doStream,true);
    ASSERT_EQ(a.message,"");
    ASSERT_EQ(a.SaveFile,"8080");
}

TEST(PARSER,RUN_WITH_ANOTHER_SAVE_AND_PORT)
{
    char* argv[5];
    *argv[0]='a';
    *argv[1]='-s';
    *argv[2]='8080';
    *argv[1]='-lp';
    *argv[2]='8080';
    int argc=5;
    Parser parser;
    auto a=parser.createProgramDriver(argc,argv);
    ASSERT_EQ(a.doStream,true);
    ASSERT_EQ(a.message,"");
    ASSERT_EQ(a.SaveFile,"8080");
    ASSERT_EQ(a.ListeningPort,8080);
}

TEST(PARSER,RUN_CONFIG)
{
    char* argv[2];
    *argv[0]='a';
    *argv[1]='-config';
    int argc=2;
    Parser parser;
    auto a=parser.createProgramDriver(argc,argv);
    ASSERT_EQ(a.doStream,false);
}

TEST(PARSER,RUN_MANUAL)
{
    char* argv[2];
    *argv[0]='a';
    *argv[1]='-h';
    int argc=2;
    Parser parser;
    auto a=parser.createProgramDriver(argc,argv);
    ASSERT_EQ(a.doStream,false);
}

TEST(PARSER,BABLY_GIVEN_ARGUMENT)
{
    char* argv[2];
    *argv[0]='a';
    *argv[1]='-lp';
    *argv[2]='-b';
    int argc=3;
    Parser parser;
    auto a=parser.createProgramDriver(argc,argv);
    ASSERT_EQ(a.doStream,false);
    ASSERT_NE(a.message,"");
}

TEST(PARSER,SAVE_ARGUMENT)
{
    char* argv[2];
    *argv[0]='a';
    *argv[1]='-config';
    int argc=2;
    Parser parser;
    auto a=parser.createProgramDriver(argc,argv);
    char* argv2[4];
    *argv2[0]='a';
    *argv2[1]='-config';
    *argv2[2]='-s';
    *argv2[3]='111111111111111';
    int argc2=4;
    parser.createProgramDriver(argc2,argv2);
    auto b=parser.createProgramDriver(argc,argv);
    ASSERT_NE(a.SaveFile,b.SaveFile);
    argv2[3]=&a.SaveFile[0];
    parser.createProgramDriver(argc2,argv2);
    b=parser.createProgramDriver(argc,argv);
    ASSERT_NE(a.SaveFile,b.SaveFile);
}



