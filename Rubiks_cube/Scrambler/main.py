from scrmble_generator import ScrmbleGenerator

generator = ScrmbleGenerator()

for i in range(5):
    scramble = generator.scramble_3by3(len_min=21, len_max=25)
    print(f"{i+1}: {' '.join(scramble)}")

