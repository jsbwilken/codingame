from dataclasses import dataclass

n = int(input())
m = int(input())

@dataclass
class Output:
    name: str
    logic_gate: str
    input_1: str
    input_2: str

    def to_bool(self, i) -> bool:
        return i == '-'

    def to_ascii(self, i) -> str:
        return "-" if i else "_"

    def eval(self, i1: str, i2: str) -> str:

        b1 = self.to_bool(i1)
        b2 = self.to_bool(i2)
        r = None
        if self.logic_gate == "AND":
            r = self.to_ascii(b1 and b2)
        elif self.logic_gate == "OR":
            r = self.to_ascii(b1 or b2)
        elif self.logic_gate == "XOR":
            r = self.to_ascii(b1 != b2)
        elif self.logic_gate == "NAND":
            r = self.to_ascii(not (b1 and b2))
        elif self.logic_gate == "NOR":
            r = self.to_ascii(not (b1 or b2))
        elif self.logic_gate == "NXOR":
            r = self.to_ascii(b1 == b2)
        else:
            raise ValueError(f"Unsupported Gate: {self.logic_gate}")

        return r
    def get_output(self) -> str:
        output: str = f"{self.name} "
        for i1, i2 in zip(self.input_1, self.input_2):
            output += self.eval(i1, i2)

        return output

signals: dict[str, str] = {}
for i in range(n):
    input_name, input_signal = input().split()
    signals[input_name] = input_signal

for i in range(m):
    output_name, _type, input_name_1, input_name_2 = input().split()
    print(Output(output_name, _type, signals[input_name_1], signals[input_name_2]).get_output())

