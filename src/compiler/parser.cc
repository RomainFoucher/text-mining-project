#include "parser.hh"

using namespace std;

TrieNode *get_trie_from_file(ifstream& input)
{
    string line;

    auto root = new TrieNode;
    while (getline(input, line))
    {
        string word;
        string nb;
        int i = 0;
        char c = line[i];
        while ( c != ' ' && c != '\t')
        {
            word.push_back(c);
            c = line[++i];
        }
        while (c == ' ' || c == '\t') c = line[++i];
        while (c != '\0')
        {
            nb.push_back(c);
            c = line[++i];
        }
        //std::cout << line << '\t' << word << '\t' << nb << std::endl;
        insert(root, word);
    }
    return root;
}

void write_trie(TrieNode* root, std::ofstream& output)
{
    // TODO
}
