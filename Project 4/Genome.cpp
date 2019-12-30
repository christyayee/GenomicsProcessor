#include "provided.h"
#include <string>
#include <vector>
#include <iostream>
#include <istream>
using namespace std;

class GenomeImpl
{
public:
    GenomeImpl(const string& nm, const string& sequence);
    static bool load(istream& genomeSource, vector<Genome>& genomes);
    int length() const;
    string name() const;
    bool extract(int position, int length, string& fragment) const;
private:
    string m_name;
    string m_sequence;
};

GenomeImpl::GenomeImpl(const string& nm, const string& sequence)
{
    m_name = nm;
    m_sequence = sequence;
}

//must be O(N) where N is # of characters
bool GenomeImpl::load(istream& genomeSource, vector<Genome>& genomes) 
{
    genomes.clear();

    string nm;
    string dna;

    string temp;
    getline(genomeSource, nm);
    if (nm[0] != '>')
        return false;
    nm = nm.substr(1);
    while (getline(genomeSource, temp))
    {
        if (temp[0] == '>')
        {
            if (nm.size() == 0 || dna.size() == 0)
                return false;
            genomes.push_back(Genome(nm, dna));
            nm = temp;
            dna = "";
        }
        else
        {
            for (int i = 0; i < temp.size(); i++)
            {
                switch(toupper(temp[i]))
                {
                    case 'A':
                    case 'C':
                    case 'G':
                    case 'T':
                    case 'N':
                        dna += toupper(temp[i]);
                        break;
                    default:
                        return false;
                }
            }
        }
    }
    if (nm.size() == 0 || dna.size() == 0)
        return false;
    genomes.push_back(Genome(nm, dna));
    nm = temp;
    
    return true;
}

//must be O(1)
int GenomeImpl::length() const
{
    return (int)(m_sequence.size());
}

//must be O(S) where S is length of name
string GenomeImpl::name() const
{
    return m_name;
}

//must be O(S) where S is length of sequence
bool GenomeImpl::extract(int position, int length, string& fragment) const
{
    if (position < 0 || length < 0 || position + length > m_sequence.size())
        return false;
    else
    {
        fragment = m_sequence.substr(position, length);
        return true;
    }
}

//******************** Genome functions ************************************

// These functions simply delegate to GenomeImpl's functions.
// You probably don't want to change any of this code.

Genome::Genome(const string& nm, const string& sequence)
{
    m_impl = new GenomeImpl(nm, sequence);
}

Genome::~Genome()
{
    delete m_impl;
}

Genome::Genome(const Genome& other)
{
    m_impl = new GenomeImpl(*other.m_impl);
}

Genome& Genome::operator=(const Genome& rhs)
{
    GenomeImpl* newImpl = new GenomeImpl(*rhs.m_impl);
    delete m_impl;
    m_impl = newImpl;
    return *this;
}

bool Genome::load(istream& genomeSource, vector<Genome>& genomes) 
{
    return GenomeImpl::load(genomeSource, genomes);
}

int Genome::length() const
{
    return m_impl->length();
}

string Genome::name() const
{
    return m_impl->name();
}

bool Genome::extract(int position, int length, string& fragment) const
{
    return m_impl->extract(position, length, fragment);
}

//in extract, can length be 0


//    genomes.clear();
//    std::string nm = "";
//    char temp;
//
//    do
//    {
//        getline(genomeSource, nm);  // read a whole line into nm
//        if (nm[0] != '>')
//            return false;
//        nm = nm.substr(1);
//
//        std::string dna = "";
//        while (genomeSource.get(temp) && temp != '>')
//        {
//            switch(toupper(temp))
//            {
//                case 'A':
//                case 'C':
//                case 'G':
//                case 'T':
//                case 'N':
//                    dna += toupper(temp);
//                    break;
//                default:
//                    return false;
//            }
//        }
//        if (nm.size() == 0 || dna.size() == 0)
//            return false;
//        genomes.push_back(Genome(nm, dna));
//
//    }while (temp == '>'); //signals successive Genomes
//
//    return true;  // This compiles, but may not be correct

