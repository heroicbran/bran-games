import pygame
BLUE = (   0,   0, 255)

#Room class
class Room():
    name = ""
    outer_dim = [0, 0]
    rects = []
    wall_list = []
    bound_list = []
    x_bound = 800
    y_bound = 600
    
    def __init__(self, name):
 
        for i in range(9):                                  #Default walls
            self.wall_list.append([-100, (i*100)])
            
            self.wall_list.append([(i*100), -100])
            
            self.wall_list.append([800, (i*100)])
            
            self.wall_list.append([(i*100), 600])
            
        #Match name with file name to generate right room obj
        file = open(name + ".txt", "r", 1)
        self.name = name
        
        self.line = file.readline()
        
        while self.line[0] != '@':                       #Skips all # (Maybe change to ! $)
	    
            if self.line[0] == "#" or self.line[0] == "" or not self.line.strip():
                self.line = file.readline()
	        print(1)

                
            elif self.line[0] == "$" or self.line[0] == "@":
	        print(2)
                break     
            
            elif len(self.line) > 0:                      # Populate room obj with walls
		if self.line[0] != "":
                  self.wall_list.append([int(self.line[0:2]), int(self.line[5:7])])
                  self.line = file.readline()
                    
       
                   
                
    def build_walls(self, screen):     # Classes MUST include self in their arguments
        if self.wall_list:
            for i in self.wall_list:
                rect = pygame.draw.rect(screen, BLUE, [i[0], i[1], 100, 100])  #x1, y1, x2, y2  (Visual indicator)
                #rect = pygame.Rect(i[0], i[1], 100, 100)                     (Invisible version)
                self.rects.append(rect)   
         
        
        #Walls = Blue rects for now
        # Default room boarder
        
        # Import other boundaries from file
        
        # Import items/mobs from file
        
    
