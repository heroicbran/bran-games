import mob
import room
from time import sleep
import pygame

pygame.init()
size = (800, 600)
screen = pygame.display.set_mode(size)
pygame.display.set_caption("Bran's Cool Game")

# Define some colors
BLACK    = (   0,   0,   0)
WHITE    = ( 255, 255, 255)
GREEN    = (   0, 255,   0)
RED      = ( 255,   0,   0)
BLUE     = (   0,   0, 255)


# Player Initialization
player_state = 0    # none (0), inv (1), menu (2), event (3), movement (4), choice (5)
mc = mob.Mob("Bran")           # Initialize Player character
img = pygame.image.load("base.bmp").convert()   #Import image
img.set_colorkey(WHITE)  # bg transparency
mc_rect = img.get_rect() # Use this rect to do collision detection!
mc_rect.x = mc.x
mc_rect.y = mc.y
inv_open = 0
menu_wait = 0
# Move Rect first, check for collision, then move if safe


#Room Initialization
curr_room = 0        # Index of current room
rooms = []
rooms.append(room.Room("test_room"))

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

    blocked = [0, 0, 0, 0]  # Down, Up, Left, and Right block states
    keys = pygame.key.get_pressed() # Returns a list of key statuses

    if keys[pygame.K_SPACE]:
        print("Rect", mc_rect.x, " ", mc_rect.y)
        print("MC", mc.x, " ", mc.y)

    if keys[pygame.K_x]:
        if inv_open == 1:
            inv_open = 0
            sleep(1)

        else:
            inv_open = 1
            sleep(1)


    if keys[pygame.K_DOWN]:
        # Loop through bounds, comparing y + 5 coord to list and change blocked to 1 if
        # a match is found. Then do an if to check if blocked[x] is 1 before continuing on.
        # After that, revert blocked
        mc_rect = mc_rect.move(0, 5)
        if mc_rect.collidelist(rooms[curr_room].rects) != -1:
            print("COLLISION D")
            mc_rect = mc_rect.move(0, -5)
        else:
            mc.y += 5

    if keys[pygame.K_UP]:
        mc_rect = mc_rect.move(0, -5)
        if mc_rect.collidelist(rooms[curr_room].rects) != -1:
            print("COLLISION U")
            mc_rect = mc_rect.move(0, 5)
        else:
            mc.y -= 5

    if keys[pygame.K_LEFT]:
        mc_rect = mc_rect.move(-5, 0)
        if mc_rect.collidelist(rooms[curr_room].rects) != -1:
            print("COLLISION L")
            mc_rect = mc_rect.move(5, 0)
        else:
            mc.x -= 5

    if keys[pygame.K_RIGHT]:
        mc_rect = mc_rect.move(5, 0)
        if mc_rect.collidelist(rooms[curr_room].rects) != -1:
            print("COLLISION R")
            mc_rect = mc_rect.move(-5, 0)
        else:
            mc.x += 5


    # --- Game logic should go here


    # Wall collision test


    # --- Drawing code should go here
    # bottom layer

    screen.fill(WHITE)
    rooms[curr_room].build_walls(screen)
    '''Draw room function'''
    '''Mobs and items draw functions'''
    '''MC draw function'''
    screen.blit(img, [mc.x, mc.y], [0, 0, 100, 100])  # x1, y1, w, h (of image)

    if inv_open == 1:
        pygame.draw.rect(screen, BLACK, [0, 400, 800, 750])  # Dialog/Inventory BlkBox
        pygame.draw.rect(screen, WHITE, [25, 425, 125, 150])  # Dialog/Inventory Pic

        pygame.draw.rect(screen, WHITE, [400, 450, 100, 100])  # Dialog/Inventory Box1
        pygame.draw.rect(screen, WHITE, [525, 450, 100, 100])  # Dialog/Inventory Box2
        pygame.draw.rect(screen, WHITE, [650, 450, 100, 100])  # Dialog/Inventory Box3
        pygame.draw.rect(screen, WHITE, [275, 450, 100, 100])  # Dialog/Inventory Box4
    # topmost layer



    # --- Go ahead and update the screen with what we've drawn.
    pygame.display.flip()

    # --- Limit to 60 frames per second
    clock.tick(60)

pygame.quit()
