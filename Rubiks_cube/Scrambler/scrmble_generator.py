from random import randint, choice
from PIL import Image, ImageDraw


class ScrmbleGenerator:
    def __init__(self):
        self.moves = ['R', 'L', 'U', 'D', 'F', 'B']
        self.direction = ['', '\'', '2']

        self.opposite = {'R': 'L',
                    'L': 'R',
                    'U': 'D',
                    'D': 'U',
                    'F': 'B',
                    'B': 'F'}

    def __scrmb_len_renew(self, len_min, len_max):
        return randint(len_min, len_max)
    
    def scramble_3by3(self, len_min=25, len_max=28):
        # set the scramble length
        self.scrmb_len = self.__scrmb_len_renew(len_min, len_max)
        
        # initialize the scramble moves list
        self.scramble = [[]]*self.scrmb_len
        
        # give random scramble
        for i in range(len(self.scramble)):
            self.scramble[i] = choice(self.moves) + choice(self.direction)
        
        # adjust the scramble, because there may have invalid moves
        # e.g. " R R' ", so replace the last 'R'
        for i in range(1, len(self.scramble)):
            while self.scramble[i][0] == self.scramble[i-1][0]:
                self.scramble[i] = self.scramble[i].replace(self.scramble[i][0], choice(self.moves))
        
        # or " R2 L R2 ", so replace 'L'
        for i in range(2, len(self.scramble)):
            if self.scramble[i][0] == self.scramble[i-2][0]:
                while self.scramble[i-1][0] == self.opposite[self.scramble[i][0]] or self.scramble[i-1][0] == self.scramble[i][0]:
                    # print(1)
                    self.scramble[i-1] = self.scramble[i-1].replace(self.scramble[i-1][0], choice(self.moves))
        
        # self.scramble = ' '.join(self.scramble)
        
        return self.scramble


class ScrambleImage:
    def __init__(self, cube_type:int=3):   
        self.cube_type = cube_type
        
        self.colors = {'U':"white", 'F':"green", 'R':"red", 'D':"yellow", 'L':"orange", 'B':"blue"}
        # self.init_faces(self.colors)
    
    def show_colors(self):
        print(self.colors)
        return self.colors
    
    def pick_colors(self, custom_color:dict):
        '''like this format: {'U':"white", 'F':"green", 'R':"red", 'D':"yellow", 'L':"orange", 'B':"blue"} '''
        pass
    
    
    def init_faces(self, colors:dict):
        self.face_U = [[colors['U'] for _ in range(self.cube_type)] for _ in range(self.cube_type)]
        self.face_F = [[colors['F'] for _ in range(self.cube_type)] for _ in range(self.cube_type)]
        self.face_R = [[colors['R'] for _ in range(self.cube_type)] for _ in range(self.cube_type)]
        self.face_D = [[colors['D'] for _ in range(self.cube_type)] for _ in range(self.cube_type)]
        self.face_L = [[colors['L'] for _ in range(self.cube_type)] for _ in range(self.cube_type)]
        self.face_B = [[colors['B'] for _ in range(self.cube_type)] for _ in range(self.cube_type)]
    
    
    def determine(self, move:str):
        layers = []
        
        if move == 'U':
            layer_l = self.face_L[0]
            layer_f = self.face_F[0]
            layer_r = self.face_R[0]
            layer_b = self.face_B[0]
            # print(id(layer_l), id(self.face_L[0]))
            
            layers = [layer_l, layer_f, layer_r, layer_b]
            
        elif move == 'F':
            layer_u = self.face_U[self.cube_type-1]
            layer_l = reversed([self.face_L[r][-1] for r in range(self.cube_type)])
            layer_d = reversed(self.face_D[0])
            layer_r = [self.face_R[r][0] for r in range(self.cube_type)]
            
            layers = [layer_u, layer_l, layer_d, layer_r]
        
        elif move == 'R':
            layer_u = [self.face_U[r][-1] for r in range(self.cube_type)]
            layer_f = [self.face_F[r][-1] for r in range(self.cube_type)]
            layer_d = [self.face_D[r][-1] for r in range(self.cube_type)]
            layer_b = reversed([self.face_B[r][0] for r in range(self.cube_type)])
            
            layers = [layer_u, layer_f, layer_d, layer_b]
        
        elif move == 'D':
            layer_r = self.face_R[-1]
            layer_f = self.face_F[-1]
            layer_l = self.face_L[-1]
            layer_b = self.face_B[-1]
            
            layers = [layer_r, layer_f, layer_l, layer_b]
        
        elif move == 'L':
            layer_d = [self.face_D[r][0] for r in range(self.cube_type)]
            layer_f = [self.face_F[r][0] for r in range(self.cube_type)]
            layer_u = [self.face_U[r][0] for r in range(self.cube_type)]
            layer_b = reversed([self.face_B[r][-1] for r in range(self.cube_type)])
            
            layers = [layer_d, layer_f, layer_u, layer_b]
        
        elif move == 'B':
            layer_u = self.face_U[0]
            layer_r = [self.face_R[r][-1] for r in range(self.cube_type)]
            layer_d = reversed(self.face_D[-1])
            layer_l = reversed([self.face_L[r][0] for r in range(self.cube_type)])
            
            layers = [layer_u, layer_r, layer_d, layer_l]
        
        # print(layers)
        
        return layers
    
    
    def turn_layer(self, layers:list, move:str) -> list:
        try:
            turning_direction = move[1]
        except IndexError:
            turning_direction = ''
        finally:
            move = move[0]

        # a layer's turning times, 90 degrees a turn
        if turning_direction == '\'':
            times = 3
        elif turning_direction == '2':
            times = 2
        else:
            times = 1
        
        # turn the layer itself
        if move == 'U':
            self.face_U = self.turn_layer_itself(self.face_U, times)
        elif move == 'F':
            self.face_F = self.turn_layer_itself(self.face_F, times)
        elif move == 'R':
            self.face_R = self.turn_layer_itself(self.face_R, times)
        elif move == 'D':
            self.face_D = self.turn_layer_itself(self.face_D, times)
        elif move == 'L':
            self.face_L = self.turn_layer_itself(self.face_L, times)
        elif move == 'B':
            self.face_B = self.turn_layer_itself(self.face_B, times)
        
        # cycle the layer list, to simulate the turning of 90 degrees
        for _ in range(times):        
            temp = layers[0]
            for i in range(1, len(layers)):
                layers[i-1] = layers[i]
            layers[-1] = temp
        
        return layers

    
    def turn_layer_itself(self, face, times):
        # 2-D list rotate clockwise
        for _ in range(times):
            face = [list(r) for r in list(zip(*face[::-1]))]
        return face
    
    
    def finish_turn(self, turning:list, move:str):
        if move == 'U':
            layer_l, layer_f, layer_r, layer_b = map(list, turning)
            self.face_L[0] = layer_l
            self.face_F[0] = layer_f
            self.face_R[0] = layer_r
            self.face_B[0] = layer_b
        
        elif move == 'F':
            layer_u, layer_l, layer_d, layer_r = map(list, turning)
            
            layer_l = layer_l[::-1]
            layer_d = layer_d[::-1]
            
            self.face_U[self.cube_type-1] = layer_u

            for r in range(self.cube_type):
                self.face_L[r][-1] = layer_l[r]
            
            self.face_D[0] = layer_d
            
            for r in range(self.cube_type):
                self.face_R[r][0] = layer_r[r]

        elif move == 'R':
            layer_u, layer_f, layer_d, layer_b = map(list, turning)
            
            # 因為B的方向相反，所以要reverse回去
            layer_b = layer_b[::-1]
            
            for r in range(self.cube_type):
                self.face_U[r][-1] = layer_u[r]
            
            for r in range(self.cube_type):
                self.face_F[r][-1] = layer_f[r]
            
            for r in range(self.cube_type):
                self.face_D[r][-1] = layer_d[r]
            
            for r in range(self.cube_type):
                self.face_B[r][0] = layer_b[r]
                
        elif move == 'D':
            layer_r, layer_f, layer_l, layer_b = map(list, turning)
            
            self.face_R[-1] = layer_r
            self.face_F[-1] = layer_f
            self.face_L[-1] = layer_l
            self.face_B[-1] = layer_b
        
        elif move == 'L':
            layer_d, layer_f, layer_u, layer_b = map(list, turning)
            
            # 因為B的方向相反，所以要reverse回去
            layer_b = layer_b[::-1]
            
            for r in range(self.cube_type):
                self.face_D[r][0] = layer_d[r]
            
            for r in range(self.cube_type):
                self.face_F[r][0] = layer_f[r]
            
            for r in range(self.cube_type):
                self.face_U[r][0] = layer_u[r]
            
            for r in range(self.cube_type):
                self.face_B[r][-1] = layer_b[r]
        
        elif move == 'B':
            layer_u, layer_r, layer_d, layer_l = map(list, turning)
            
            # 也是很類似B，因為每面的編號的關係，導致有些需要reverse才會對到正確的位置
            layer_d = layer_d[::-1]
            layer_l = layer_l[::-1]
            
            self.face_U[0] = layer_u
            
            for r in range(self.cube_type):
                self.face_R[r][-1] = layer_r[r]
            
            self.face_D[-1] = layer_d
            
            for r in range(self.cube_type):
                self.face_L[r][0] = layer_l[r]

    
    def text_img(self, scramble:str):
        self.init_faces(self.colors)
        
        for move in scramble:
            layers = self.determine(move[0])
            
            turning = self.turn_layer(layers, move)
            
            self.finish_turn(turning, move[0])
    
    
    def text_img_show(self):
        print("U\n", self.face_U)
        print("F\n", self.face_F)
        print("R\n", self.face_R)
        print("D\n", self.face_D)
        print("L\n", self.face_L)
        print("B\n", self.face_B)
    
    
    def image_3by3(self, scramble):
        self.text_img(scramble)
        
        self.img = Image.new("RGB", (1250, 935), "white")
        self.cube_pattern = ImageDraw.Draw(self.img)
        
        cube_side_len = 100
        
        border = 10
        # w1 = border
        # h1 = border
        # w2 = w1 + cube_side_len
        # h2 = h1 + cube_side_len
        
        for round in range(1, 4):
            if round == 1:
                face = self.face_U
                
                for i in range(self.cube_type):
                    w1 = border * 2 + cube_side_len * (self.cube_type)
                    h1 = border + cube_side_len * (i)
                    w2 = w1 + cube_side_len
                    h2 = h1 + cube_side_len
                    for j in range(self.cube_type):
                        color = face[i][j]
                        self.cube_pattern.rectangle(((w1, h1), (w2, h2)), fill=color, outline="black", width=2)
                        
                        w1 = w2
                        w2 += cube_side_len
            
            elif round == 2:
                faces = [self.face_L, self.face_F, self.face_R, self.face_B]
                
                for i in range(self.cube_type):
                    w1 = border
                    h1 = border * 2 + cube_side_len * (i + self.cube_type)
                    w2 = w1 + cube_side_len
                    h2 = h1 + cube_side_len
                    for face in faces:
                        for j in range(self.cube_type):
                            color = face[i][j]
                            self.cube_pattern.rectangle(((w1, h1), (w2, h2)), fill=color, outline="black", width=2)
                            
                            w1 = w2
                            w2 += cube_side_len
                        w1 += border
                        w2 += border

            elif round == 3:
                face = self.face_D
                
                for i in range(self.cube_type):
                    w1 = border * 2 + cube_side_len * (3)
                    h1 = border * 3 + cube_side_len * (i + self.cube_type * 2)
                    w2 = w1 + cube_side_len
                    h2 = h1 + cube_side_len
                    for j in range(self.cube_type):
                        color = face[i][j]
                        self.cube_pattern.rectangle(((w1, h1), (w2, h2)), fill=color, outline="black", width=2)
                        
                        w1 = w2
                        w2 += cube_side_len

    
    def show(self, img_width=400, img_height=300):
        '''img width and height in pixels'''
        self.img = self.img.resize((img_width, img_height))
        
        self.img.show()



# if __name__ == '__main__':
#     generator = ScrmbleGenerator()
#     scramble = generator.scramble_3by3()
#     print(' '.join(scramble))
#     
#     img = ScrambleImage(3)
#     img.image_3by3(scramble)
#     img.show(1250, 935)
