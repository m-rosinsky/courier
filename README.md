# Courier

Courier is a lightweight scripting language with a focus on writing quick and dirty client/server applications.

The language is written in C++11.

## Concept and Features

Courier offers a multitude of built-in features to facilitate easy creation of client/server programs.

Some key features include:

1. Built-in serialization/deserialization schemes
2. Pre-made modularized scripts for tasks such as:
    - HTTP servers
    - FTP client/servers
    - Simple socket clients
3. Expansive bit-manipulation operators for working with bit fields
4. Custom fixed width data types

## Syntax

Courier is a strongly-typed procedural programming language.

The syntax can be loosely compared to C/C++, but differs in some key ways.

### Hello World

This program demonstrates a simple hello world program written in Courier:

```
i32 main()
{
    out("Hello, World!");
}
```

All integers in Courier have their widths defined, similar to Rust.

In the above example, the return type for the ```main``` function is an ```i32```, or a 32-bit signed integer.

### Bit Field Operators

Courier offers built-in operators for working with bit-fields, which are very useful when dealing with serialized data over a network.

For example, let's say we wanted to get bit 2-5 (0-indexed inclusive) out of a byte.

In C, we would write something like this:

```C
uint8_t byte = 0b10101010;  // Bits 2-5 are 1010
uint8_t mask = 0x3c;        // 00111100
uint8_t result = (byte & mask) >> 2; // Apply mask and shift.
```

In Courier, we can simply use a built-in operator to solve this without masks or bit-shifts.

```C
u8 byte = b10101010;
u4 result = byte<2:5>; // result -> 1010
```

Not only are we able to make use of a built-in bit-field operator: ```<>```, but we are also able to create a custom fixed-width integer that matches the number of bits we extract (```u4```).

In a second example, let's say we simply want to set a bit within a byte to ```1```, while preserving the value of all other bits.

This is extremely useful in protocols that use bit-fields smaller than a byte.

In C, we would write:

```C
uint8_t byte = 0b00000000;

// Set the 6th bit to 1 while preserving the other bits.
uint8_t mask = 0b00000010;
byte = byte | mask;
```

In Courier, we can simply use a bit operator to set a specific bit:

```C
u8 byte = b00000000;
byte<6> = 1; // byte -> b00000010
```

We can also set a range of bits to a specific value with the same operator:

```C
u8 byte = b00000000;
byte<4:6> = b111; // byte -> b00001110.
```

## Serialization and Deserialization

Courier makes sending and receiving data over a socket much more streamlined.

Let's take a look at an example protocol:

``````
Protocol Structure:

+----------+----------+----------+----------+
| Byte 1   | Byte 2   | Byte 3   | Byte 4   |
+----------+----------+----------+----------+
| OOOIIIII | 11112222 | DDDDDDDD | DDDDDDDD |
+----------+----------+----------+----------+

Protocol Breakdown:

- Byte 1:
  - First 3 bits: Opcode (0 to 7) indicating the operation type.
  - Last 5 bits: Instruction (0 to 31) specifying the specific action to be taken.

- Byte 2:
  - First 4 bits: arg1 (0 to 15) providing the first argument for the operation.
  - Second 4 bits: arg2 (0 to 15) providing the second argument for the operation.

- Bytes 3-4 (Data):
  - 16 bits of data used for additional information or parameters related to the operation.
``````

We can define a custom datatype in Courier to easily handle this:

```C
field msg
{
    u3 opcode;
    u5 instr;
    u4 arg1;
    u4 arg2;
    u16 data;
}
```

Creating a sending this message over a socket becomes trivial:

```C
msg my_msg = {
    opcode = b101,
    instr  = b11100,
    arg1   = b1010,
    arg2   = b0101,
    data   = x1234  // Hex (\x12\x34)
};

sock.send(my_msg);
```

Receiving becomes trivial as well:

```C
bstring data = sock.recv(msg.size); // bytestring data type.
msg my_msg = unpack(data); // Unpack raw bytes into the msg field.
```

The data fields are unpacked into the message field with one function.
