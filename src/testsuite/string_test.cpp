#include "../dlo/output.hpp"
#include "../dlo/stringutils.hpp"

int main(){
	using namespace dlo::stringutils;
	using dlo::notef;
	using dlo::note;
	using dlo::error;
	using dlo::errorf;
	
	uint fails = 0;
	
	notef(0, "testing dlo::stringutils::%s()...","text");
	if(text(1,2.5,"foo",'b','a','r') == "12.5foobar"){
		note(0,"success.");
	}
	else{
		++fails;
		error("failed!");
	}
	
	notef(0, "testing dlo::stringutils::%s()...","textf");
	if(textf("foo %s bar %3s, %2s, %0s","1",2,3.5,'c') 
		== "foo 1 bar 3.5, 2, foo %s bar %3s, %2s, %0s"){
		note(0,"success.");
	}
	else{
		++fails;
		error("failed!");
	}
	
	notef(0, "testing dlo::stringutils::%s()...","strip");
	if(strip(" \t foo bar \t ") == "foo bar"){
		note(0,"success.");
	}
	else{
		++fails;
		error("failed!");
	}
	
	notef(0, "testing dlo::stringutils::%s()...","split");
	if(split("foo:bar:baz",":") 
		== (std::vector<std::string>{"foo", "bar", "baz"}) ){
		note(0,"success.");
	}
	else{
		++fails;
		error("failed!");
	}
	
	
	notef(0, "testing dlo::stringutils::%s()...","split_once");
	auto tmp = split_once("foo:bar:baz",":");
	if((tmp.first == "foo")&&(tmp.second == "bar:baz")){
		note(0,"success.");
	}
	else{
		++fails;
		error("failed!");
	}
	
	
	notef(0, "testing dlo::stringutils::%s()...","decode");
	if(decode("\"foo\\t\\n\\\\\\\"\"") == "foo\t\n\\\""){
		note(0,"success.");
	}
	else{
		++fails;
		error("failed!");
	}
	
	
	notef(0, "testing dlo::stringutils::%s()...","prefix_and_align");
	if(prefix_and_align("foo ","bar\nbaz") == "foo bar\n    baz"){
		note(0,"success.");
	}
	else{
		++fails;
		error("failed!");
	}
	
	if(fails){
		errorf("%s tests failed", fails);
		return 1;
	}
	else{
		note(0,"all tests were succesfull");
		return 0;
	}
}