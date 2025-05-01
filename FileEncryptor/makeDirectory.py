import os
import string
import random

long_sentences = [
    "Although the sun had barely risen, casting a golden hue over dew-covered fields where rabbits darted and birds chirped, Maria walked along the trail, haunted by dreams of faceless voices whispering lost secrets, feeling a strange sense of déjà vu she couldn’t shake, and as she passed ancient trees and mossy stones, something seemed to call her forward, urging her to seek answers in the wind, the shadows, and the fragments of memory that flickered in her mind—poetry, old songs, a vanished boy, and the well that, legend said, led not to water, but to another world.",
    
    "Despite the chaos erupting outside the library windows where protesters clashed with riot police amid smoke and shouting, Professor Halberg remained focused at his oak desk, translating a forgotten Latin manuscript that spoke of a lost desert civilization which built towers with light and spoke to stars, and as he made connections to quantum theory, he realized this text could reveal that history wasn’t linear, but cyclical, hiding truths about past human peaks now buried in time, and just maybe, he thought, the real knowledge of the universe wasn’t in new discoveries—but in rediscovering what was once already known.",
    
    "After the storm had battered the coastal village for days, tearing roofs, flooding streets, and beaching boats, the townspeople emerged to survey the damage, and while most saw only destruction, young Elias saw something else—an electric blue light deep beneath the waves that had glowed through the chaos like an eye watching from the sea floor, and although his father laughed and called it imagination, Elias was certain he had seen something ancient awaken in the storm’s heart, something that pulsed not just with energy but with memory, as if the sea itself had remembered and responded to a call.",
    
    "In the final minutes before launch, as the astronauts were strapped tightly into their seats, heartbeats echoing in their helmets and the thunder of engines growing louder beneath them, Commander Lin closed her eyes and thought not of Mars, the red planet that awaited them, but of Earth—of her mother’s hands planting tomatoes, her son’s laughter, the feel of wind on her skin—because she knew this mission, historic and daring though it was, could very well be her last, and if it was, she wanted to carry not fear but the warmth of life with her into the stars.",
    
    "The clockmaker worked in silence, the only sounds the ticking of hundreds of clocks lining the walls and the gentle scratch of his tools, and though no one knew his real name, townsfolk came from far away to buy his creations, each said to keep time not just perfectly but differently, as if attuned to something more than just minutes and hours—some claimed their clocks predicted events, others that they replayed lost moments, and though the clockmaker never confirmed or denied these stories, he always smiled faintly, as if he knew something about time that others never would.",
    
    "On the night the sky turned green, people first thought it was an aurora or some strange weather anomaly, but when the lights began to pulse rhythmically and objects in the sky formed geometric shapes never seen before, even the most skeptical scientists paused, and in the weeks that followed, strange phenomena occurred: children speaking unknown languages, compasses spinning wildly, dreams shared by strangers across continents, and while governments scrambled to maintain order and deny what they couldn’t explain, a quiet revolution of thought had already begun—people sensed it deep down, that the world had irreversibly changed overnight.",
    
    "Beneath the city, far below the streets and sewers, there is a tunnel that leads to a chamber untouched by time, where murals of impossible creatures decorate the walls and a pool of still water reflects not the face of the visitor but the memory of the last time they truly knew themselves, and those who find it—few as they are—return changed, speaking less, dreaming more, and sometimes disappearing entirely, as if the place has claimed a part of them forever, and though urban explorers whisper of it in forums and blogs, no map ever marks its entrance twice.",
    
    "He built the cabin with his own hands, deep in the forest where no roads led and no phone signal reached, not because he hated people, but because he wanted to remember who he was without noise, screens, and the constant pull of other people’s needs, and over time, the birds became his neighbors, the trees his guardians, and the stars his evening companions, until one day he found he no longer needed to speak aloud, because the silence had taught him its own language, and in that language, he discovered a kind of peace he never knew he was missing.",
    
    "At the edge of the desert, where sand meets cracked stone and the wind sings low through jagged canyons, stands a tower with no door, no windows, and no known origin, yet travelers report strange dreams when sleeping nearby—visions of a spiral staircase winding upward forever, voices whispering numbers, and a sense that something waits at the top, watching, always watching, and though many have tried to climb it in their dreams, few reach the summit, and those who do often wake changed, eyes distant, as if they’ve glimpsed a truth so large it no longer fits in words.",
    
    "In the hospital room where the machines hummed and monitors blinked softly, a boy sat beside his grandfather’s bed, reading aloud from a dusty book of old myths the elder had once loved, and though the old man had not spoken in days, his hand twitched at certain names, his breath caught at certain lines, and as the boy read the final tale—the story of a soul that journeys through darkness to find the light—it seemed to him that something passed between them, unseen but deeply felt, and when the last page turned, the old man’s eyes finally closed."
]


def makeFiles(path):
    os.makedirs(path, exist_ok=True)
    os.chdir(path)
    for i in range(1000):
        file_name = f"test{i+1}.txt"
        with open(file_name, "w") as file:
            text_for_file = random.choice(long_sentences)
            file.write(text_for_file)

if __name__ == "__main__":
    makeFiles("test")