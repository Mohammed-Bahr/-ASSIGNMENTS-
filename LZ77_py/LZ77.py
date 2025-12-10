class LZ77:
    def _init_(self, search_window, lookahead_buffer_size):
        self.search_window = 20
        self.lookahead_buffer_size = 20

    def encode(self, data):
        encoded = []
        i = 0
        n = len(data)
        while i < n:
            search_start = max(0, i - self.search_window)
            search_buffer = data[search_start:i]
            lookahead_buffer = data[i:i + self.lookahead_buffer_size]
            match_position = 0
            match_length = 0
            MAX_OFFSET = 10

            for j in range(len(search_buffer)):
                length = 0
                while (length < len(lookahead_buffer) and
                       length < len(search_buffer) - j and
                       search_buffer[j + length] == lookahead_buffer[length]):
                    length += 1
                    distance = len(search_buffer) - j
                    if distance <= MAX_OFFSET:
                        if length > match_length or (length == match_length and distance < match_position):
                            match_length = length
                            match_position = distance

            next_char = lookahead_buffer[match_length] if match_length < len(lookahead_buffer) else ''
            encoded.append((match_position, match_length, next_char))
            i += match_length + 1
        return encoded

    def decode(self, encoded_data):
        decoded = []
        for position, length, next_char in encoded_data:
            if position > 0 and length > 0:
                start_pos = len(decoded) - position
                if start_pos < 0:
                    raise ValueError("Invalid encoded data: position larger than current output length")
                for j in range(length):
                    decoded.append(decoded[start_pos + j])
            if next_char:
                decoded.append(next_char)
            print(f"Step {position+1}: {decoded}")
        return ''.join(decoded)


if  __name__ == "__main__":
    lz77 = LZ77(search_window=20, lookahead_buffer_size=20)
    
    while True:
        print("Welcome to LZ77 Compressor & Decomperssor")
        choice = input("""What would you like to do?
1)Encode 
2)Decode
3)Exit
Choose from(1/2/3):""")
        
        if choice == '3':
            print("it's a pleasure to help you [=^_^=]")
            break
            
        if choice == '1':
            text = input("Enter text to compress: ")
            encoded = lz77.encode(text)
            print("\nEncoded data:")
            print(encoded)
            
        elif choice == '2':
            print("Please make sure to enter encoded data in format [(position, length, char), ...]:")
            try:
                encoded_input = eval(input())
                print("\nDecoding steps (decoded array at each step):")
                decoded = lz77.decode(encoded_input)
                print("\nFinal Decoded String:")
                print(decoded)
            except:
                print("Invalid input format! Please enter data in correct format.")
                
        else:
            print("Invalid choice! Please select 1, 2, or 3 (-_-).")
        
        print("\n" + "="*50 + "\n")