use std::cmp; //add import
use crossterm::event::*;
use crate::editorrows::EditorRows;

pub struct CursorController {
    pub cursor_x: usize,
    pub cursor_y: usize,
	screen_rows: usize,
    screen_columns: usize,
    pub row_offset: usize,
	pub column_offset: usize,
	  
}

impl CursorController {
    pub fn new(win_size: (usize, usize)) -> CursorController {
        Self {
            cursor_x: 0,
            cursor_y: 0,
            screen_columns: win_size.0,
            screen_rows: win_size.1,
            row_offset: 0,
			column_offset:0 // add initialiser
        }
    }
    /* modify the function*/
    pub fn move_cursor(&mut self, direction: KeyCode, editor_rows: &EditorRows) {
        let number_of_rows = editor_rows.number_of_rows();

        match direction {
            KeyCode::Up => {
                self.cursor_y = self.cursor_y.saturating_sub(1);
            }
            KeyCode::Left => {
                if self.cursor_x != 0 {
                    self.cursor_x -= 1;
                } else if self.cursor_y > 0 {
                    self.cursor_y -= 1;
                    self.cursor_x = editor_rows.get_editor_row(self.cursor_y).render.len();
                }
            }
            KeyCode::Down => {
                if self.cursor_y < number_of_rows {
                    self.cursor_y += 1;
                }
            }
            KeyCode::End => {
                /* add the following*/
                if self.cursor_y < number_of_rows {
                    self.cursor_x = editor_rows.get_editor_row(self.cursor_y).render.len();
                }
            }
            /* ene */
            KeyCode::Home => self.cursor_x = 0,
            _ => unimplemented!(),
        }
        let row_len = if self.cursor_y < number_of_rows {
            editor_rows.get_editor_row(self.cursor_y).render.len()
        } else {
            0
        };
        self.cursor_x = cmp::min(self.cursor_x, row_len);
    }
	pub fn scroll(&mut self) {
        self.row_offset = cmp::min(self.row_offset, self.cursor_y);
        if self.cursor_y >= self.row_offset + self.screen_rows {
            self.row_offset = self.cursor_y - self.screen_rows + 1;
        }
    }
}