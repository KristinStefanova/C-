#include <iostream>
#include <fstream>
#include "Node.h"
#include "HuffmanTree.h"
using namespace std;
/*---------------------------------------- TEST ------------------------------------------------------------*/
void test()
{
    HuffmanTree one;
    string message, encoded, decoded;

    cout << "Enter message to encode: ";
    getline(cin, message);

    encoded = one.encodeMessage(message);
    cout << "Code: " << encoded << endl;

    cout << "Numbers: ";
    one.from8bitBinariesToDecimals(encoded);
    cout << endl;

    cout << "Ratio of compression: " << one.ratio(message, encoded) << endl;

    decoded = one.decodeMessage(encoded);
    cout << "Decoded message: " << decoded << endl;

    HuffmanTree two;
    string filename;
    cout << "Enter a file name: ";
    cin >> filename;

    encoded = two.encodeMessageFromFile(filename);
    cout << "Code: " << encoded << endl;

    cout << "Numbers: ";
    two.from8bitBinariesToDecimals(encoded);
    cout << endl;

    cout << "Ratio of compression: " << two.ratio(message, encoded) << endl;

    decoded = two.decodeMessage(encoded);
    cout << "Decoded message: " << endl << decoded << endl;

}

int main()
{
    test();
    return 0;
}
