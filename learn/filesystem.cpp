#include<experimental/filesystem>
int main(){
    std::experimental::filesystem::create_directory("file");
    return 0;
}

