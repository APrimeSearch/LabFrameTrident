//
//  main.cpp
//  trident_tester
//
//  Created by Natalia Toro on 2014-12-20.
//  Copyright (c) 2014 Natalia Toro. All rights reserved.
//

#include <iostream>

int test_FourVector();
int test_ParticleType();
int test_Particle();
int test_Event();
int test_SimplifiedAPEXPhaseSpaceSelector();

int main(int argc, const char * argv[]) {

    int i;
    
    /*
    if((i=test_FourVector()) !=0){
        std::cout << "Four vector test failed!";
        return i;
    };
    
    
    if((i=test_ParticleType()) !=0){
        std::cout << "Particle type test failed!";
        return i;
    };
    return 0;
     
    if((i=test_Particle()) !=0){
        std::cout << "Particle test failed!";
        return i;
    };*/

    if((i=test_SimplifiedAPEXPhaseSpaceSelector()) !=0){
        std::cout << "Event test failed!";
        return i;
    };
    
    if((i=test_Event()) !=0){
        std::cout << "Event test failed!";
        return i;
    };
    return 0;
    
}

