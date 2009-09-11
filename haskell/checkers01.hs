
main = do
    (newboard, playerA, playerB) <- getConfig
    play newboard playerA playerB

play newBoard playerA playerB = do
    displayBoard newBoard
    makeMove newBoard White
    where
        makeMove board side = do
            let player = getPlayer side
            afterMove <- if canAttack board side
                then attackLoop player board side
                else player Move board side
            let nextBoard = upgradeToKings afterMove
            displayBoard nextBoard
            if isVictory side nextBoard
                then return ("Winner is " ++ show side)
                else makeMove nextBoard (otherSide side)

        attackLoop player board side = do
            board' <- player Attack board side
            if canAttack board' side
                then attackLoop player board' side
                else return board'
        
        getPlayer White = playerA
        getPlayer Black = playerB
        
        isVictory = undefined
        canAttack = undefined


data MoveType = Move | Attack
data Side = White | Black deriving Show
otherSide White = Black
otherSide Black = White

getConfig = undefined
getRandom = undefined
displayBoard = undefined
upgradeToKings = undefined
move = undefined
attack = undefined
availableMoves = undefined
availableAttacks = undefined

randomComputer Attack board side = do
    v <- getRandom (availableAttacks board side)
    return $ attack board side v

randomComputer Move board side =
    case availableMoves board side of
        []  -> return board
        variants -> do return $ move board side (getRandom variants)



