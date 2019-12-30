////
////  main.cpp
////  Project 4
////
////  Created by Christy Yee on 3/7/19.
////  Copyright © 2019 Christy Yee. All rights reserved.
////
//
//#include <iostream>
//#include <fstream>
//#include <string>
//#include "Trie.h"
//#include "provided.h"
//
//using namespace std;
//
//int main(int argc, const char * argv[])
//{
////    Trie<int> tree;
////    tree.insert(TEST,1);
////    cout << "yay";
////    tree.insert("ACGT", 5);
////    tree.insert("ACGT", 3);
////    tree.insert("ACG", 1);
////    tree.insert("AC", 2);
////    tree.insert("A", 4);
//////    tree.insert("", 0);
////
//////    //all off by one
////    tree.insert("ACCT", 6);
////    tree.insert("ACTT", 7);
////    tree.insert("ATGT", 8);
////    tree.insert("CCGT", 0);
////
////    //off by two
////    tree.insert("AGCT", 9);
////
////    vector<int> allValues = tree.find("ACGT", false);
////    for (int i = 0; i < allValues.size(); i++)
////        cout << allValues[i];
////    cout << endl;
////    allValues = tree.find("A", false);
////    for (int i = 0; i < allValues.size(); i++)
////        cout << allValues[i];
////
////    cout << endl;
////    tree.print();
//    
////    ifstream infile("/Users/christy/Library/Mobile Documents/com~apple~ButtDocs/Winter Quarter/CS32/Project 4/Gee-nomics/data/Halobacterium_jilantaiense.txt");
////    if (infile)
////    {
////        vector<Genome> g;
////        bool success = Genome::load(infile, g);
////        if (success)
////        {
////            GenomeMatcher gm(1);
////            cout << "work bitch" << endl;
////            for (int i = 0; i < g.size(); i++)
////            {
////                gm.addGenome(g[i]);
////                cout << i << endl;
////            }
////            cout << endl << "yay bitch" << endl;
////        }
////        else
////            cout << "fuck bitch" << endl;
////    }
////    else
////        cout << "error shit" << endl;
//    
////    GenomeMatcher g(4);
////    Genome add("Genome 1" , "CGGTGTACNACGACTGGGGATAGAATATCTTGACGTCGTACCGGTTGTAGTCGTTCGACCGAAGGGTTCCGCGCCAGTAC");
////    g.addGenome(add);
////    Genome add2("Genome 2","TAACAGAGCGGTNATATTGTTACGAATCACGTGCGAGACTTAGAGCCAGAATATGAAGTAGTGATTCAGCAACCAAGCGG");
////    g.addGenome(add2);
////    Genome add3("Genome 3", "TTTTGAGCCAGCGACGCGGCTTGCTTAACGAAGCGGAAGAGTAGGTTGGACACATTNGGCGGCACAGCGCTTTTGAGCCA");
////    g.addGenome(add3);
////    vector<DNAMatch> matches;
////    bool result;
////
////    result = g.findGenomesWithThisDNA("GAAG",    4,    true,    matches);
////    cout << "TEST CASE 1" << endl;
////    if (!result)
////        cout << "returns FALSE" << endl;
////    for(int i=0; i<matches.size(); i++)
////        cout << matches[i].genomeName << " of length " << matches[i].length <<" at position " << matches[i].position << endl;
////    cout << endl;
////
////    result = g.findGenomesWithThisDNA("GAATAC",    4,    true,    matches);
////    cout << "TEST CASE 2" << endl;
////    if (!result)
////        cout << "returns FALSE" << endl;
////    for(int i=0; i<matches.size(); i++)
////        cout << matches[i].genomeName << " of length " << matches[i].length <<" at position " << matches[i].position << endl;
////    cout << endl;
////
////    result = g.findGenomesWithThisDNA("GAATAC",    6,    true,    matches);
////    cout << "TEST CASE 3" << endl;
////    if (!result)
////        cout << "returns FALSE" << endl;
////    for(int i=0; i<matches.size(); i++)
////        cout << matches[i].genomeName << " of length " << matches[i].length <<" at position " << matches[i].position << endl;
////    cout << endl;
////
////    result = g.findGenomesWithThisDNA("GAATAC",    6,    false,    matches);
////    cout << "TEST CASE 4" << endl;
////    if (!result)
////        cout << "returns FALSE" << endl;
////    for(int i=0; i<matches.size(); i++)
////        cout << matches[i].genomeName << " of length " << matches[i].length <<" at position " << matches[i].position << endl;
////    cout << endl;
////
////    result = g.findGenomesWithThisDNA("GTATAT",    6,    false,    matches);
////    cout << "TEST CASE 5" << endl;
////    if (!result)
////        cout << "returns FALSE" << endl;
////    for(int i=0; i<matches.size(); i++)
////        cout << matches[i].genomeName << " of length " << matches[i].length <<" at position " << matches[i].position << endl;
////    cout << endl;
////
////    result    =    g.findGenomesWithThisDNA("GAATACG",    6,    false,    matches);
////    cout << "TEST CASE 6" << endl;
////    if (!result)
////        cout << "returns FALSE" << endl;
////    for(int i=0; i<matches.size(); i++)
////        cout << matches[i].genomeName << " of length " << matches[i].length <<" at position " << matches[i].position << endl;
////    cout << endl;
////
////    result    =    g.findGenomesWithThisDNA("GAAGGGTT",    5,    false,    matches);
////    cout << "TEST CASE 7" << endl;
////    if (!result)
////        cout << "returns FALSE" << endl;
////    for(int i=0; i<matches.size(); i++)
////        cout << matches[i].genomeName << " of length " << matches[i].length <<" at position " << matches[i].position << endl;
////    cout << endl;
////
////    result    =    g.findGenomesWithThisDNA("GAAGGGTT",    6,    false,    matches);
////    cout << "TEST CASE 8" << endl;
////    if (!result)
////        cout << "returns FALSE" << endl;
////    for(int i=0; i<matches.size(); i++)
////        cout << matches[i].genomeName << " of length " << matches[i].length <<" at position " << matches[i].position << endl;
////    cout << endl;
////
////    result    =    g.findGenomesWithThisDNA("ACGTGCGAGACTTAGAGCC",    12,    false,    matches);
////    cout << "TEST CASE 9" << endl;
////    if (!result)
////        cout << "returns FALSE" << endl;
////    for(int i=0; i<matches.size(); i++)
////        cout << matches[i].genomeName << " of length " << matches[i].length <<" at position " << matches[i].position << endl;
////    cout << endl;
////
////    result    =    g.findGenomesWithThisDNA("ACGTGCGAGACTTAGAGCG",    12,    false,    matches);
////    cout << "TEST CASE 10" << endl;
////    if (!result)
////        cout << "returns FALSE" << endl;
////    for(int i=0; i<matches.size(); i++)
////        cout << matches[i].genomeName << " of length " << matches[i].length <<" at position " << matches[i].position << endl;
////    cout << endl;
////
////    result    =    g.findGenomesWithThisDNA("GAAG",    3,    true,    matches);
////    cout << "TEST CASE 11" << endl;
////    if (!result)
////        cout << "returns FALSE" << endl;
////    for(int i=0; i<matches.size(); i++)
////        cout << matches[i].genomeName << " of length " << matches[i].length <<" at position " << matches[i].position << endl;
////    cout << endl;
////
////    result    =    g.findGenomesWithThisDNA("GAAG",    5,    true,    matches);
////    cout << "TEST CASE 12" << endl;
////    if (!result)
////        cout << "returns FALSE" << endl;
////    for(int i=0; i<matches.size(); i++)
////        cout << matches[i].genomeName << " of length " << matches[i].length <<" at position " << matches[i].position << endl;
////    cout << endl;
//    
//    GenomeMatcher gm(4);
//    Genome nome("sasquatch", "GGGGTTTTAAAACCCCACGTACGTACGTNANANANA");
//    vector<GenomeMatch> results;
//    gm.addGenome(nome);
//    Genome query("q", "AAATCCCTGGGGTTTTNANA");
//    gm.findRelatedGenomes(query, 8, false, 20, results);
//    for(int i = 0; i < results.size(); i++)
//        cout << results[i].genomeName << " with percent match of " << results[i].percentMatch << "%" << endl;
//    cout << endl;
//    
//    
//}
//
////GAAGAGTAGGTTGG


