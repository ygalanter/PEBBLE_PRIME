#include <pebble.h>
#include "utils.h"
 
Window* window;
TextLayer *text_layer_start, *text_layer_start_label;
TextLayer *text_layer_prime, *text_layer_prime_label;
TextLayer *text_layer_reset_label;

char buffer[10], buffer_prime[10];
uint iStart = 0;
uint iPrimeStart = 0;


void text_layer_set_number(TextLayer *i_text_layer, uint number1, char *abuffer) {
   itoa(number1, abuffer, 10);
   text_layer_set_text(i_text_layer, abuffer); 
}


TextLayer *text_layer_setup(GRect frame, GFont font, GTextAlignment text_alignment, Layer *window){
  
  TextLayer *text_layer = text_layer_create(frame);
  text_layer_set_font(text_layer, font);
  text_layer_set_text_alignment(text_layer, text_alignment);
  layer_add_child(window, (Layer*)text_layer);

  return text_layer;
}




void up_click_handler(ClickRecognizerRef recognizer, void *context)
{
    iStart += 1000;
    iPrimeStart = iStart;
    memset(buffer_prime,0,sizeof(buffer_prime));
    text_layer_set_number(text_layer_start, iStart, buffer);
    
}
 
void down_click_handler(ClickRecognizerRef recognizer, void *context)
{
 
    iStart = 0;
    iPrimeStart = 0;
    memset(buffer,0,sizeof(buffer));
    memset(buffer_prime,0,sizeof(buffer_prime));
    text_layer_set_number(text_layer_start, iStart, buffer);
    
}
 
void select_click_handler(ClickRecognizerRef recognizer, void *context)
{
  iPrimeStart = get_prime(iPrimeStart);
  text_layer_set_number(text_layer_prime,  iPrimeStart, buffer_prime);
      
}

void click_config_provider(void *context)
{
    window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
    window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
    window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
}

 
/* Load all Window sub-elements */
void window_load(Window *window)
{
    Layer *window_layer = window_get_root_layer(window);
  
    text_layer_start_label = text_layer_setup(GRect(5, 0, 139, 28), fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD), GTextAlignmentCenter, window_layer);
    text_layer_set_text(text_layer_start_label, "Set Start ->");
  
    text_layer_start = text_layer_setup(GRect(5, 28, 139, 28), fonts_get_system_font(FONT_KEY_GOTHIC_28), GTextAlignmentCenter, window_layer);
    text_layer_set_number(text_layer_start, iStart, buffer);
  
    text_layer_prime_label = text_layer_setup(GRect(5, 56, 139, 28), fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD), GTextAlignmentCenter, window_layer);
    text_layer_set_text(text_layer_prime_label, "Next Prime ->");
  
    text_layer_prime = text_layer_setup(GRect(5, 84, 139, 28), fonts_get_system_font(FONT_KEY_GOTHIC_28), GTextAlignmentCenter, window_layer);
    text_layer_set_number(text_layer_prime, 1, buffer_prime);
  
    text_layer_reset_label = text_layer_setup(GRect(5, 112, 139, 28), fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD), GTextAlignmentCenter, window_layer);
    text_layer_set_text(text_layer_reset_label, "Reset ->");
}
 
/* Un-load all Window sub-elements */
void window_unload(Window *window)
{
    text_layer_destroy(text_layer_start_label);
    text_layer_destroy(text_layer_start);
    text_layer_destroy(text_layer_prime_label);
    text_layer_destroy(text_layer_prime);
    text_layer_destroy(text_layer_reset_label);
}
 
/* Initialize the main app elements */
void init()
{
    window = window_create();
    WindowHandlers handlers = {
        .load = window_load,
        .unload = window_unload
    };
    window_set_window_handlers(window, (WindowHandlers) handlers);
    window_set_click_config_provider(window, click_config_provider);
    window_stack_push(window, true);
}
 
/* De-initialize the main app elements */
void deinit()
{
    window_destroy(window);
}
 
/* Main app lifecycle */
int main(void)
{
    init();
    app_event_loop();
    deinit();
}