#include "provided.h"
#include "Trie.h"
#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <algorithm>
using namespace std;

class GenomeMatcherImpl
{
public:
    GenomeMatcherImpl(int minSearchLength);
    void addGenome(const Genome& genome);
    int minimumSearchLength() const;
    bool findGenomesWithThisDNA(const string& fragment, int minimumLength, bool exactMatchOnly, vector<DNAMatch>& matches) const;
    bool findRelatedGenomes(const Genome& query, int fragmentMatchLength, bool exactMatchOnly, double matchPercentThreshold, vector<GenomeMatch>& results) const;
private:
    int m_min;
    Trie<DNAMatch> m_tree;
    unordered_map<string,Genome> m_genomes;
    void findHelper(const string& fragment, bool exactMatchOnly, DNAMatch* dna, const string& sequence, int pos) const;
};

//must be O(1)
GenomeMatcherImpl::GenomeMatcherImpl(int minSearchLength)
{
    m_min = minSearchLength;
}

//must be O(L*N) where L is minSearchLength and N is length of dna sequence
void GenomeMatcherImpl::addGenome(const Genome& genome)
{
    m_genomes.emplace(genome.name(), genome);
    string extract = "";
    int i = 0;
    while (genome.extract(i, m_min, extract))
    {
        DNAMatch dna;
        dna.position = i;
        dna.genomeName = genome.name();
        dna.length = 0;
        m_tree.insert(extract, dna);
        i++;
    }
}

//must be O(1)
int GenomeMatcherImpl::minimumSearchLength() const
{
    return m_min;
}

//must be O(H*F) where F is length of fragment, H is # of distinct hits
bool GenomeMatcherImpl::findGenomesWithThisDNA(const string& fragment, int minimumLength, bool exactMatchOnly, vector<DNAMatch>& matches) const
{
    matches.clear();
    if (minimumLength < minimumSearchLength() || fragment.size() < minimumLength)
        return false;
    vector<DNAMatch> result = m_tree.find(fragment.substr(0, m_min),exactMatchOnly);
    unordered_map<string, DNAMatch> tempmap;
    unordered_map<string, DNAMatch> :: iterator it;
    
    for (int i = 0; i < result.size(); i++)
    {
        //result[i] is a DNAMatch
        string sequence = "";
        Genome current = m_genomes.at(result[i].genomeName);
        int pos = result[i].position;
        int remaining = current.length() - pos;
        if (fragment.size() <= remaining)
            current.extract(pos, (int)(fragment.size()), sequence);
        else
            current.extract(pos, remaining, sequence);

        //updates length of DNAMatch
        findHelper(fragment, exactMatchOnly, &result[i], sequence, 0);
        
        //accounts for Genome with duplicate positions
        it = tempmap.find(result[i].genomeName);
        if (it == tempmap.end())//not present
            tempmap.emplace(result[i].genomeName, result[i]);
        else//DNAMatch with same Genome exists
        {
            if (result[i].length > it->second.length)
                it->second = result[i];
            else if (it->second.length == result[i].length &&  result[i].position < it->second.position)
                it->second = result[i];
        }
    }
    it = tempmap.begin();
    while (it != tempmap.end())
    {
        if (it->second.length >= minimumLength)
            matches.push_back(it->second);
        it++;
    }
    
    return (matches.size()>0);
}

//runs O(F) where F is length of fragment
void GenomeMatcherImpl::findHelper(const string& fragment, bool exactMatchOnly, DNAMatch* dna, const string& sequence, int pos) const
{
    if (pos == fragment.size() || pos == sequence.size())
        return;
    if (sequence[pos] == fragment[pos])
    {
        dna->length++;
        return findHelper(fragment, exactMatchOnly, dna, sequence, pos+1);
    }
    else
    {
        if (!exactMatchOnly)
        {
            dna->length++;
            return findHelper(fragment, true, dna, sequence, pos+1);
        }
    }
}

//call find to return vector of DNAMatches to first m_min length of fragment
//use vector to get genome names to access Genome from map
//use to access full sequence
    //extract() sequence to one length longer
    //compare extract()ed sequence with fragment substr one length longer
    //increment length of DNAMatch
    //if exactMatchOnly, continue while fragment == extracted
    //if !exactMatchOnly, continue while fragment == extracted (SNiPs not found),
        //when SNiPs found, correct fragment
        //set exactMatchOnly to true, continue while fragment == extracted
//at end, have vector of DNAMatches with starting pos, Genome, length
//check for DNAMatches with same name

//return true if one before two
bool compare(const GenomeMatch& one, const GenomeMatch& two)
{
    if (one.percentMatch > two.percentMatch)
        return true;
    else if (one.percentMatch == two.percentMatch && one.genomeName < two.genomeName)
        return true;
    return false;
}

//must have O(Q*X) where Q is length of queries and X is O() of findGenomesWithThisDNA()s
bool GenomeMatcherImpl::findRelatedGenomes(const Genome& query, int fragmentMatchLength, bool exactMatchOnly, double matchPercentThreshold, vector<GenomeMatch>& results) const
{
    if (fragmentMatchLength < m_min)
        return false;
    results.clear();
    int totalSeq = 0;
    string strQuery = "";
    vector<DNAMatch> matches;
    unordered_map<string, int> map;
    unordered_map<string, int> :: iterator it;
    
    while (query.extract(totalSeq*fragmentMatchLength, fragmentMatchLength, strQuery) )
    {
        if (findGenomesWithThisDNA(strQuery, fragmentMatchLength, exactMatchOnly, matches))
        {
            for (DNAMatch match: matches)
            {
                it = map.find(match.genomeName);
                if (it != map.end()) //genomeName already present in map
                    (it->second)++;
                else //must add genomeName to map
                    map.emplace(match.genomeName, 1);
            }
        }
        totalSeq++;
    }
    
    it = map.begin();
    while (it != map.end())
    {
        double percent = (double)(it->second)/totalSeq;

        if (100*percent >= matchPercentThreshold)
        {
            GenomeMatch gmatch;
            gmatch.genomeName = it->first;
            gmatch.percentMatch = 100*percent;
            results.push_back(gmatch);
        }
        it++;
    }
    
    //sort so that highest percent first, for ties: alphabetical order
    sort(results.begin(), results.end(), &compare);
    
    return (results.size() > 0);
}

//count variable to count # of total sequences
//loop to for query extractions
//call findGenomes

//unordered_map<string genomeName, int numSeq>
//take the vector that findGenomesWithThisData() returns
//loop through the vector, increment unordered_map for every DNAMatch genomeName

//******************** GenomeMatcher functions ********************************

// These functions simply delegate to GenomeMatcherImpl's functions.
// You probably don't want to change any of this code.

GenomeMatcher::GenomeMatcher(int minSearchLength)
{
    m_impl = new GenomeMatcherImpl(minSearchLength);
}

GenomeMatcher::~GenomeMatcher()
{
    delete m_impl;
}

void GenomeMatcher::addGenome(const Genome& genome)
{
    m_impl->addGenome(genome);
}

int GenomeMatcher::minimumSearchLength() const
{
    return m_impl->minimumSearchLength();
}

bool GenomeMatcher::findGenomesWithThisDNA(const string& fragment, int minimumLength, bool exactMatchOnly, vector<DNAMatch>& matches) const
{
    return m_impl->findGenomesWithThisDNA(fragment, minimumLength, exactMatchOnly, matches);
}

bool GenomeMatcher::findRelatedGenomes(const Genome& query, int fragmentMatchLength, bool exactMatchOnly, double matchPercentThreshold, vector<GenomeMatch>& results) const
{
    return m_impl->findRelatedGenomes(query, fragmentMatchLength, exactMatchOnly, matchPercentThreshold, results);
}
