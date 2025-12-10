# **LZ77 Compressor & Decompressor**

This is a simple command-line implementation of the LZ77 lossless data compression algorithm in Python. The script provides an interactive menu to either encode (compress) a string or decode (decompress) a list of LZ77 tuples.

## **Features**

* **Encode:** Compresses a given string into a series of (offset, length, next\_character) tuples.  
* **Decode:** Decompresses a list of LZ77 tuples back into the original string.  
* **Interactive CLI:** A simple menu to choose between encoding, decoding, or exiting the program.  
* **Step-by-Step Decoding:** Shows the state of the decoded data after each tuple is processed.

## **How to Run**

1. Save the code as a Python file (e.g., lz77.py).  
2. Run the script from your terminal:  
   python lz77.py

## **Usage**

Once the script is running, you will see a welcome message and a menu with three options.

### **1\) Encode**

This option will compress a string you provide.

1. Choose option 1\.  
2. Enter the text you want to compress (e.g., banana).  
3. The script will output the compressed data.

**Example:**

What would you like to do?  
1)Encode   
2)Decode  
3)Exit  
Choose from(1/2/3):1  
Enter text to compress: banana

Encoded data:  
\[(0, 0, 'b'), (0, 0, 'a'), (0, 0, 'n'), (2, 1, 'n'), (2, 1, '')\]

### **2\) Decode**

This option will decompress a list of LZ77 tuples.

1. Choose option 2\.  
2. Enter the encoded data in the exact format of a Python list of tuples.  
   Important: You must include the square brackets, parentheses, and quotes exactly as shown.  
3. The script will show the decoding process step-by-step and print the final decompressed string.

**Example:**

What would you like to do?  
1)Encode   
2)Decode  
3)Exit  
Choose from(1/2/3):2  
Please make sure to enter encoded data in format \[(position, length, char), ...\]:  
\[(0, 0, 'b'), (0, 0, 'a'), (0, 0, 'n'), (2, 1, 'n'), (2, 1, '')\]

Decoding steps (decoded array at each step):  
Step 1: \['b'\]  
Step 2: \['b', 'a'\]  
Step 3: \['b', 'a', 'n'\]  
Step 3: \['b', 'a', 'n', 'a', 'n'\]  
Step 3: \['b', 'a', 'n', 'a', 'n', 'a'\]

Final Decoded String:  
banana

*(Note: The "Step" number printed during decoding corresponds to the position value \+ 1, which may not be sequential.)*

### **3\) Exit**

This option will stop the program.

## **Implementation Notes**

* **Hardcoded Values:**  
  * In the \_\_init\_\_ method, the search\_window and lookahead\_buffer\_size are hardcoded to 20, ignoring any parameters that might be passed when creating the LZ77 object.  
  * Inside the encode method, MAX\_OFFSET is hardcoded to 10\. This means the algorithm will only find matches within the 10 characters immediately preceding the lookahead buffer, even though the search buffer may be larger.  
* **eval() Usage:** The decode feature uses eval() to parse the user's input. This is generally unsafe and should not be used in a production environment as it can execute arbitrary Python code.  
* **Offset/Position:** The position value in the encoded tuple represents the offset (distance) from the current position *backwards* into the already-decoded text. A value of 0 means no match was found.
