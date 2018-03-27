import pygame
pygame.init()
size = (700, 500)
screen = pygame.display.set_mode(size)
pygame.display.set_caption("Bran's Cool Game")

# Define some colors
BLACK    = (   0,   0,   0)
WHITE    = ( 255, 255, 255)
GREEN    = (   0, 255,   0)
RED      = ( 255,   0,   0)
BLUE     = (   0,   0, 255)

# Mob Class
class Mob():
    name = ""                            
    loc = [0,0] # X and Y coords
    speed = 5
    
    def __init__(self, a):  # A costructor
        self.name = a              #Use self for non-shared stuff
        
    def behav():
        
        

# MC Info
mc = Mob("Bran")
img = pygame.image.load("base.bmp").convert()


# Loop until the user clicks the close button.
done = False

# Used to manage how fast the screen updates
clock = pygame.time.Clock()

# -------- Main Program Loop -----------
pygame.key.set_repeat(1, 1)
while not done:
    # --- Main event loop
    if pygame.event.get(pygame.QUIT):
        done = True
    
    keys = pygame.key.get_pressed() # Returns a list of key statuses
    
    if keys[pygame.K_DOWN]:
        mc.loc[1] += 3
        
    if keys[pygame.K_UP]:
        mc.loc[1] -= 3
        
    if keys[pygame.K_LEFT]:
        mc.loc[0] -= 3
            
    if keys[pygame.K_RIGHT]:
        mc.loc[0] += 3                                   
                


    # --- Game logic should go here

    # --- Drawing code should go here

    screen.fill(WHITE)
    '''Draw room function'''
    '''Mobs and items draw functions'''
    '''MC draw function'''
    screen.blit(img, mc.loc, [100, 0, 20, 32])  # learn trick?
    pygame.draw.rect(screen, BLUE, [650, 0, 50, 50])
    # at top left
    
    

    # --- Go ahead and update the screen with what we've drawn.
    pygame.display.flip()

    # --- Limit to 60 frames per second
    clock.tick(60)
    
pygame.quit()